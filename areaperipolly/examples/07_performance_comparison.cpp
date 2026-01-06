/**
 * @file 07_performance_comparison.cpp
 * @brief Performance comparison between different approaches
 * @author Magpiny
 * @date 2026
 *
 * This example demonstrates:
 * - Performance measurement
 * - Comparing float vs double
 * - Large polygon handling
 * - Optimization techniques
 */

#include "areaperipoly.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <random>
#include <vector>

using namespace geometry;
using namespace std::chrono;

std::vector<Point2D<double>> generate_random_polygon(size_t n,
                                                     double radius = 100.0) {
  std::mt19937 gen(42); // Fixed seed for reproducibility
  std::uniform_real_distribution<double> dis(0.9, 1.1);

  std::vector<Point2D<double>> vertices;
  vertices.reserve(n);

  for (size_t i = 0; i < n; ++i) {
    double angle = 2.0 * std::numbers::pi * static_cast<double>(i) /
                   static_cast<double>(n);
    double r = radius * dis(gen);
    vertices.emplace_back(r * std::cos(angle), r * std::sin(angle));
  }

  return vertices;
}

template <typename T>
void benchmark_calculation(const std::string &type_name, size_t vertices,
                           size_t iterations) {
  std::cout << "\n--- " << type_name << " with " << vertices
            << " vertices ---\n";

  // Generate polygon
  auto poly_d = generate_random_polygon(vertices);
  std::vector<Point2D<T>> poly;
  for (const auto &p : poly_d) {
    poly.emplace_back(static_cast<T>(p.x.value), static_cast<T>(p.y.value));
  }

  // Warm-up
  for (size_t i = 0; i < 100; ++i) {
    auto area = calculate_area_shoelace<T>(poly);
    (void)area;
  }

  // Benchmark area calculation
  auto start = high_resolution_clock::now();
  for (size_t i = 0; i < iterations; ++i) {
    auto area = calculate_area_shoelace<T>(poly);
    (void)area; // Prevent optimization
  }
  auto end = high_resolution_clock::now();

  auto duration = duration_cast<nanoseconds>(end - start).count();
  double avg_ns =
      static_cast<double>(duration) / static_cast<double>(iterations);

  std::cout << "  Total time: "
            << static_cast<double>(duration) / static_cast<double>(1000000.0)
            << " ms\n";
  std::cout << "  Average time: " << avg_ns << " ns per calculation\n";
  std::cout << "  Throughput: " << (1e9 / avg_ns) << " calculations/second\n";
}

int main() {
  std::cout << "=== Performance Comparison ===\n";
  std::cout << std::fixed << std::setprecision(2);

  const size_t iterations = 100000;

  std::cout << "\n╔═══════════════════════════════════════════════════════╗\n";
  std::cout << "║  Small Polygons (Triangle - 3 vertices)              ║\n";
  std::cout << "╚═══════════════════════════════════════════════════════╝\n";

  benchmark_calculation<float>("float", 3, iterations);
  benchmark_calculation<double>("double", 3, iterations);

  std::cout << "\n╔═══════════════════════════════════════════════════════╗\n";
  std::cout << "║  Medium Polygons (20 vertices)                        ║\n";
  std::cout << "╚═══════════════════════════════════════════════════════╝\n";

  benchmark_calculation<float>("float", 20, iterations);
  benchmark_calculation<double>("double", 20, iterations);

  std::cout << "\n╔═══════════════════════════════════════════════════════╗\n";
  std::cout << "║  Large Polygons (100 vertices)                        ║\n";
  std::cout << "╚═══════════════════════════════════════════════════════╝\n";

  benchmark_calculation<float>("float", 100, iterations / 10);
  benchmark_calculation<double>("double", 100, iterations / 10);

  std::cout << "\n╔═══════════════════════════════════════════════════════╗\n";
  std::cout << "║  Very Large Polygons (1000 vertices)                  ║\n";
  std::cout << "╚═══════════════════════════════════════════════════════╝\n";

  benchmark_calculation<float>("float", 1000, iterations / 100);
  benchmark_calculation<double>("double", 1000, iterations / 100);

  std::cout << "\n=== Summary ===\n";
  std::cout << "- float is typically faster due to better cache utilization\n";
  std::cout
      << "- double provides higher precision (~15 vs ~7 decimal digits)\n";
  std::cout << "- Performance scales linearly with vertex count O(n)\n";
  std::cout << "- Modern CPUs can calculate millions of polygons per second\n";

  return 0;
}
