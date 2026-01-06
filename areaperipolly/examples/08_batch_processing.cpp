/**
 * @file 08_batch_processing.cpp
 * @brief Batch processing multiple polygons
 * @author Magpiny
 * @date 2026
 *
 * This example shows:
 * - Processing multiple polygons efficiently
 * - Statistical analysis
 * - Aggregate calculations
 * - Data pipeline patterns
 */

#include "areaperipoly.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace geometry;

struct PolygonData {
  std::string id;
  std::vector<Point2D<double>> vertices;
  double area = 0.0;
  double perimeter = 0.0;
};

std::vector<PolygonData> generate_sample_data(size_t count) {
  std::mt19937 gen(42);
  std::uniform_int_distribution<> vertex_dis(3, 12);
  std::uniform_real_distribution<> coord_dis(-100.0, 100.0);

  std::vector<PolygonData> data;
  data.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    PolygonData poly;
    poly.id = "POLY_" + std::to_string(i + 1);

    size_t num_vertices = static_cast<size_t>(vertex_dis(gen));
    poly.vertices.reserve(num_vertices);

    // Generate vertices on a circle with random radius
    double radius = coord_dis(gen) + 50.0;
    for (size_t j = 0; j < num_vertices; ++j) {
      double angle = 2.0 * std::numbers::pi * static_cast<double>(j) /
                     static_cast<double>(num_vertices);
      poly.vertices.emplace_back(radius * std::cos(angle),
                                 radius * std::sin(angle));
    }

    data.push_back(std::move(poly));
  }

  return data;
}

void process_batch(std::vector<PolygonData> &data) {
  std::cout << "\n--- Processing " << data.size() << " polygons ---\n";

  size_t success_count = 0;
  size_t failure_count = 0;

  for (auto &poly : data) {
    auto area = calculate_area_shoelace(poly.vertices);
    auto perimeter = calculate_perimeter(poly.vertices);

    if (area && perimeter) {
      poly.area = area->value;
      poly.perimeter = perimeter->value;
      ++success_count;
    } else {
      ++failure_count;
    }
  }

  std::cout << "Success: " << success_count << "\n";
  std::cout << "Failures: " << failure_count << "\n";
}

void print_statistics(const std::vector<PolygonData> &data) {
  std::cout << "\n╔═══════════════════════════════════════════════════════╗\n";
  std::cout << "║              STATISTICAL ANALYSIS                     ║\n";
  std::cout << "╚═══════════════════════════════════════════════════════╝\n";

  // Extract areas and perimeters
  std::vector<double> areas;
  std::vector<double> perimeters;

  for (const auto &poly : data) {
    if (poly.area > 0.0) {
      areas.push_back(poly.area);
      perimeters.push_back(poly.perimeter);
    }
  }

  if (areas.empty()) {
    std::cout << "No valid data to analyze.\n";
    return;
  }

  // Calculate statistics
  auto area_sum = std::accumulate(areas.begin(), areas.end(), 0.0);
  auto perim_sum = std::accumulate(perimeters.begin(), perimeters.end(), 0.0);

  double area_mean = area_sum / static_cast<double>(areas.size());
  double perim_mean = perim_sum / static_cast<double>(perimeters.size());

  auto area_min = *std::min_element(areas.begin(), areas.end());
  auto area_max = *std::max_element(areas.begin(), areas.end());
  auto perim_min = *std::min_element(perimeters.begin(), perimeters.end());
  auto perim_max = *std::max_element(perimeters.begin(), perimeters.end());

  // Calculate standard deviation
  double area_variance = 0.0;
  double perim_variance = 0.0;

  for (const auto &area : areas) {
    area_variance += (area - area_mean) * (area - area_mean);
  }
  for (const auto &perim : perimeters) {
    perim_variance += (perim - perim_mean) * (perim - perim_mean);
  }

  area_variance /= static_cast<double>(areas.size());
  perim_variance /= static_cast<double>(perimeters.size());

  double area_stddev = std::sqrt(area_variance);
  double perim_stddev = std::sqrt(perim_variance);

  // Print statistics
  std::cout << std::fixed << std::setprecision(2);

  std::cout << "\n--- AREA STATISTICS ---\n";
  std::cout << "  Count: " << areas.size() << "\n";
  std::cout << "  Total: " << area_sum << " square units\n";
  std::cout << "  Mean: " << area_mean << " square units\n";
  std::cout << "  Std Dev: " << area_stddev << " square units\n";
  std::cout << "  Min: " << area_min << " square units\n";
  std::cout << "  Max: " << area_max << " square units\n";

  std::cout << "\n--- PERIMETER STATISTICS ---\n";
  std::cout << "  Mean: " << perim_mean << " units\n";
  std::cout << "  Std Dev: " << perim_stddev << " units\n";
  std::cout << "  Min: " << perim_min << " units\n";
  std::cout << "  Max: " << perim_max << " units\n";
}

void print_top_polygons(const std::vector<PolygonData> &data, size_t top_n) {
  std::cout << "\n--- TOP " << top_n << " LARGEST POLYGONS (by area) ---\n";

  std::vector<const PolygonData *> sorted_data;
  for (const auto &poly : data) {
    if (poly.area > 0.0) {
      sorted_data.push_back(&poly);
    }
  }

  std::sort(sorted_data.begin(), sorted_data.end(),
            [](const auto *a, const auto *b) { return a->area > b->area; });

  std::cout << std::fixed << std::setprecision(2);

  for (size_t i = 0; i < std::min(top_n, sorted_data.size()); ++i) {
    const auto &poly = *sorted_data[i];
    std::cout << "  " << (i + 1) << ". " << poly.id << " - Area: " << poly.area
              << ", Perimeter: " << poly.perimeter
              << ", Vertices: " << poly.vertices.size() << "\n";
  }
}

int main() {
  std::cout << "=== Batch Processing Example ===\n";

  // Generate sample data
  std::cout << "\nGenerating sample data...\n";
  auto data = generate_sample_data(100);

  // Process all polygons
  process_batch(data);

  // Print statistics
  print_statistics(data);

  // Print top polygons
  print_top_polygons(data, 10);

  std::cout << "\n=== Batch Processing Complete ===\n";

  return 0;
}
