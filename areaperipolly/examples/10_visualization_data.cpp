/**
 * @file 10_visualization_data.cpp
 * @brief Generate data for visualization tools
 * @author Magpiny
 * @date 2026
 *
 * This example shows:
 * - Exporting polygon data to JSON
 * - Exporting to CSV
 * - Integration with plotting tools
 * - Data export patterns
 */

#include "areaperipoly.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace geometry;

void export_to_json(const std::vector<Point2D<double>> &vertices,
                    const std::string &filename) {
  std::ofstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filename << "\n";
    return;
  }

  auto area = calculate_area_shoelace(vertices);
  auto perimeter = calculate_perimeter(vertices);

  file << "{\n";
  file << "  \"polygon\": {\n";
  file << "    \"vertices\": [\n";

  for (size_t i = 0; i < vertices.size(); ++i) {
    file << "      {\"x\": " << vertices[i].x.value
         << ", \"y\": " << vertices[i].y.value << "}";
    if (i < vertices.size() - 1)
      file << ",";
    file << "\n";
  }

  file << "    ],\n";
  file << "    \"properties\": {\n";
  file << "      \"vertex_count\": " << vertices.size() << ",\n";

  if (area) {
    file << "      \"area\": " << area->value << ",\n";
  }
  if (perimeter) {
    file << "      \"perimeter\": " << perimeter->value << "\n";
  }

  file << "    }\n";
  file << "  }\n";
  file << "}\n";

  file.close();
  std::cout << "Exported to JSON: " << filename << "\n";
}

void export_to_csv(const std::vector<Point2D<double>> &vertices,
                   const std::string &filename) {
  std::ofstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filename << "\n";
    return;
  }

  file << "index,x,y\n";

  for (size_t i = 0; i < vertices.size(); ++i) {
    file << i << "," << vertices[i].x.value << "," << vertices[i].y.value
         << "\n";
  }

  file.close();
  std::cout << "Exported to CSV: " << filename << "\n";
}

void export_to_svg(const std::vector<Point2D<double>> &vertices,
                   const std::string &filename) {
  std::ofstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filename << "\n";
    return;
  }

  // Find bounding box
  double min_x = vertices[0].x.value, max_x = vertices[0].x.value;
  double min_y = vertices[0].y.value, max_y = vertices[0].y.value;

  for (const auto &v : vertices) {
    min_x = std::min(min_x, v.x.value);
    max_x = std::max(max_x, v.x.value);
    min_y = std::min(min_y, v.y.value);
    max_y = std::max(max_y, v.y.value);
  }

  double width = max_x - min_x + 20;
  double height = max_y - min_y + 20;

  file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
  file << "<svg xmlns=\"http://www.w3.org/2000/svg\" ";
  file << "width=\"" << width << "\" height=\"" << height << "\" ";
  file << "viewBox=\"" << (min_x - 10) << " " << (min_y - 10) << " ";
  file << width << " " << height << "\">\n";

  // Draw polygon
  file << "  <polygon points=\"";
  for (size_t i = 0; i < vertices.size(); ++i) {
    file << vertices[i].x.value << "," << vertices[i].y.value;
    if (i < vertices.size() - 1)
      file << " ";
  }
  file << "\" fill=\"lightblue\" stroke=\"blue\" stroke-width=\"2\"/>\n";

  // Draw vertices
  for (const auto &v : vertices) {
    file << "  <circle cx=\"" << v.x.value << "\" cy=\"" << v.y.value
         << "\" r=\"3\" fill=\"red\"/>\n";
  }

  file << "</svg>\n";

  file.close();
  std::cout << "Exported to SVG: " << filename << "\n";
}

int main() {
  std::cout << "=== Visualization Data Export ===\n\n";

  // Create sample polygons
  std::vector<Point2D<double>> pentagon = {
      {50.0, 10.0}, {90.0, 40.0}, {70.0, 80.0}, {30.0, 80.0}, {10.0, 40.0}};

  std::vector<Point2D<double>> star = {
      {50.0, 10.0}, {60.0, 40.0}, {90.0, 40.0}, {65.0, 60.0}, {75.0, 90.0},
      {50.0, 70.0}, {25.0, 90.0}, {35.0, 60.0}, {10.0, 40.0}, {40.0, 40.0}};

  // Export pentagon
  std::cout << "Exporting pentagon...\n";
  export_to_json(pentagon, "pentagon.json");
  export_to_csv(pentagon, "pentagon.csv");
  export_to_svg(pentagon, "pentagon.svg");

  std::cout << "\nExporting star...\n";
  export_to_json(star, "star.json");
  export_to_csv(star, "star.csv");
  export_to_svg(star, "star.svg");

  std::cout << "\n=== Export Complete ===\n";
  std::cout << "\nYou can now:\n";
  std::cout << "- View SVG files in a web browser\n";
  std::cout << "- Import CSV into Excel/plotting tools\n";
  std::cout << "- Use JSON in web applications\n";

  return 0;
}
