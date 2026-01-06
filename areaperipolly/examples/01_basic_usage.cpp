/**
 * @file 01_basic_usage.cpp
 * @brief Basic usage examples of the PolygonGeometry library
 * @author Magpiny
 * @date 2026
 *
 * This example demonstrates:
 * - Creating simple polygons
 * - Calculating areas using the Shoelace theorem
 * - Calculating perimeters
 * - Working with different polygon types
 */

#include "areaperipoly.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

using namespace geometry;

int main() {
  std::cout << "=== PolygonGeometry: Basic Usage ===\n\n";

  // Set output precision for better readability
  std::cout << std::fixed << std::setprecision(2);

  // Example 1: Triangle
  std::cout << "1. Triangle Example\n";
  std::cout << "   Creating a right triangle with base=4, height=3\n";

  std::vector<Point2D<double>> triangle = {
      {0.0, 0.0}, // Origin
      {4.0, 0.0}, // Base
      {0.0, 3.0}  // Height
  };

  auto tri_area = calculate_area_shoelace(triangle);
  auto tri_perimeter = calculate_perimeter(triangle);

  if (tri_area && tri_perimeter) {
    std::cout << "   Area: " << tri_area->value << " square units\n";
    std::cout << "   Perimeter: " << tri_perimeter->value << " units\n";
    std::cout << "   Expected area: 6.00 (base × height / 2)\n\n";
  }

  // Example 2: Square
  std::cout << "2. Square Example\n";
  std::cout << "   Creating a square with side length 5\n";

  std::vector<Point2D<double>> square = {
      {0.0, 0.0}, {5.0, 0.0}, {5.0, 5.0}, {0.0, 5.0}};

  auto square_area = calculate_area_shoelace(square);
  auto square_perimeter = calculate_perimeter(square);

  if (square_area && square_perimeter) {
    std::cout << "   Area: " << square_area->value << " square units\n";
    std::cout << "   Perimeter: " << square_perimeter->value << " units\n\n";
  }

  // Example 3: Regular Pentagon
  std::cout << "3. Regular Pentagon Example\n";
  std::cout << "   Creating a regular pentagon with side length 10\n";

  auto pentagon_area = calculate_regular_polygon_area(5, 10.0);
  auto pentagon_perimeter = calculate_regular_polygon_perimeter(5, 10.0);

  if (pentagon_area && pentagon_perimeter) {
    std::cout << "   Area: " << pentagon_area->value << " square units\n";
    std::cout << "   Perimeter: " << pentagon_perimeter->value << " units\n\n";
  }

  // Example 4: Rectangle
  std::cout << "4. Rectangle Example\n";
  std::cout << "   Width: 8, Height: 3\n";

  auto rect_area = calculate_rectangle_area(8.0, 3.0);
  auto rect_perimeter = calculate_rectangle_perimeter(8.0, 3.0);

  if (rect_area && rect_perimeter) {
    std::cout << "   Area: " << rect_area->value << " square units\n";
    std::cout << "   Perimeter: " << rect_perimeter->value << " units\n\n";
  }

  // Example 5: Circle
  std::cout << "5. Circle Example\n";
  std::cout << "   Radius: 7\n";

  auto circle_area = calculate_circle_area(7.0);
  auto circle_circumference = calculate_circle_circumference(7.0);

  if (circle_area && circle_circumference) {
    std::cout << "   Area: " << circle_area->value << " square units\n";
    std::cout << "   Circumference: " << circle_circumference->value
              << " units\n\n";
  }

  // Example 6: Irregular polygon
  std::cout << "6. Irregular Polygon Example\n";
  std::cout << "   Creating a custom shape\n";

  std::vector<Point2D<double>> custom = {
      {0.0, 0.0}, {3.0, 0.0}, {4.0, 2.0}, {2.0, 4.0}, {-1.0, 2.0}};

  auto custom_area = calculate_area_shoelace(custom);
  auto custom_perimeter = calculate_perimeter(custom);

  if (custom_area && custom_perimeter) {
    std::cout << "   Area: " << custom_area->value << " square units\n";
    std::cout << "   Perimeter: " << custom_perimeter->value << " units\n\n";
  }

  std::cout << "=== Example Complete ===\n";

  return 0;
}
