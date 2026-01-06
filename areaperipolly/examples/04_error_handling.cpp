/**
 * @file 04_error_handling.cpp
 * @brief Demonstrates error handling with std::optional
 * @author Examples
 * @date 2026
 *
 * This example shows:
 * - Handling invalid inputs gracefully
 * - Using std::optional for error checking
 * - Validation before calculations
 * - Best practices for robust code
 */

#include "areaperipoly.hpp"
#include <iomanip>
#include <iostream>
#include <optional>
#include <vector>

using namespace geometry;

void try_calculate_area(const std::vector<Point2D<double>> &vertices,
                        const std::string &description) {
  std::cout << "\nTrying: " << description << "\n";
  std::cout << "Vertices: " << vertices.size() << "\n";

  auto area = calculate_area_shoelace(vertices);

  if (area) {
    std::cout << "✓ Success! Area = " << area->value << " square units\n";
  } else {
    std::cout << "✗ Failed! Invalid polygon (need at least 3 vertices)\n";
  }
}

void try_regular_polygon(size_t sides, double side_length,
                         const std::string &description) {
  std::cout << "\nTrying: " << description << "\n";
  std::cout << "Sides: " << sides << ", Side length: " << side_length << "\n";

  auto area = calculate_regular_polygon_area(sides, side_length);

  if (area) {
    std::cout << "✓ Success! Area = " << area->value << " square units\n";
  } else {
    std::cout
        << "✗ Failed! Invalid parameters (need ≥3 sides, positive length)\n";
  }
}

void try_rectangle(double width, double height,
                   const std::string &description) {
  std::cout << "\nTrying: " << description << "\n";
  std::cout << "Width: " << width << ", Height: " << height << "\n";

  auto area = calculate_rectangle_area(width, height);

  if (area) {
    std::cout << "✓ Success! Area = " << area->value << " square units\n";
  } else {
    std::cout << "✗ Failed! Invalid dimensions (need positive values)\n";
  }
}

int main() {
  std::cout << "=== Error Handling Examples ===\n";
  std::cout << std::fixed << std::setprecision(2);

  // Valid cases
  std::cout << "\n--- Valid Inputs ---\n";

  try_calculate_area({{0.0, 0.0}, {1.0, 0.0}, {0.5, 1.0}}, "Valid triangle");

  try_regular_polygon(6, 5.0, "Valid hexagon");
  try_rectangle(10.0, 5.0, "Valid rectangle");

  // Invalid cases
  std::cout << "\n--- Invalid Inputs ---\n";

  try_calculate_area({{0.0, 0.0}, {1.0, 1.0}}, "Polygon with only 2 vertices");

  try_calculate_area({}, "Empty vertex list");

  try_regular_polygon(2, 5.0, "Polygon with 2 sides");
  try_regular_polygon(5, -3.0, "Negative side length");
  try_regular_polygon(5, 0.0, "Zero side length");

  try_rectangle(-10.0, 5.0, "Negative width");
  try_rectangle(10.0, 0.0, "Zero height");

  // Demonstrating proper error handling pattern
  std::cout << "\n--- Recommended Error Handling Pattern ---\n";

  std::vector<Point2D<double>> user_input = {{0.0, 0.0}, {1.0, 0.0}};

  if (user_input.size() < 3) {
    std::cout << "Error: Need at least 3 vertices for a polygon.\n";
  } else {
    auto area = calculate_area_shoelace(user_input);
    if (area) {
      std::cout << "Calculated area: " << area->value << "\n";
    }
  }

  std::cout << "\n=== Example Complete ===\n";

  return 0;
}
