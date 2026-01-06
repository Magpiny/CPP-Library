/**
 * @file 02_polygon_class.cpp
 * @brief Demonstrates usage of the Polygon class
 * @author Examples
 * @date 2026
 *
 * This example shows:
 * - Creating Polygon objects
 * - Accessing polygon properties
 * - Working with polygon vertices
 * - Validation and error checking
 */

#include "areaperipoly.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

using namespace geometry;

void print_polygon_info(const Polygon<double> &poly, const std::string &name) {
  std::cout << "\n--- " << name << " ---\n";
  std::cout << "Valid: " << (poly.is_valid() ? "Yes" : "No") << "\n";
  std::cout << "Vertices: " << poly.vertex_count() << "\n";

  if (poly.is_valid()) {
    auto area = poly.area();
    auto perimeter = poly.perimeter();

    if (area) {
      std::cout << "Area: " << area->value << " square units\n";
    }
    if (perimeter) {
      std::cout << "Perimeter: " << perimeter->value << " units\n";
    }

    // Display vertices
    std::cout << "Vertices:\n";
    auto vertices = poly.vertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
      std::cout << "  [" << i << "] (" << vertices[i].x.value << ", "
                << vertices[i].y.value << ")\n";
    }
  }
}

int main() {
  std::cout << "=== Polygon Class Usage ===\n";
  std::cout << std::fixed << std::setprecision(2);

  // Example 1: Valid hexagon
  std::vector<Point2D<double>> hexagon_vertices = {
      {2.0, 0.0},  {1.0, 1.732},   {-1.0, 1.732},
      {-2.0, 0.0}, {-1.0, -1.732}, {1.0, -1.732}};

  Polygon hexagon(hexagon_vertices);
  print_polygon_info(hexagon, "Regular Hexagon");

  // Example 2: Rectangle as polygon
  std::vector<Point2D<double>> rect_vertices = {
      {0.0, 0.0}, {10.0, 0.0}, {10.0, 5.0}, {0.0, 5.0}};

  Polygon rectangle(rect_vertices);
  print_polygon_info(rectangle, "Rectangle");

  // Example 3: Invalid polygon (too few vertices)
  std::vector<Point2D<double>> invalid_vertices = {{0.0, 0.0}, {1.0, 1.0}};

  Polygon invalid_poly(invalid_vertices);
  print_polygon_info(invalid_poly, "Invalid Polygon");

  // Example 4: Star shape
  std::vector<Point2D<double>> star_vertices = {
      {0.0, 10.0},  // Top
      {2.0, 4.0},   // Inner right
      {8.0, 4.0},   // Outer right
      {3.0, 0.0},   // Lower right
      {5.0, -6.0},  // Bottom
      {0.0, -2.0},  // Lower center
      {-5.0, -6.0}, // Bottom left
      {-3.0, 0.0},  // Lower left
      {-8.0, 4.0},  // Outer left
      {-2.0, 4.0}   // Inner left
  };

  Polygon star(star_vertices);
  print_polygon_info(star, "10-Point Star");

  std::cout << "\n=== Example Complete ===\n";

  return 0;
}
