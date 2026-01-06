/**
 * @file 03_different_types.cpp
 * @brief Demonstrates using different floating-point types
 * @author Examples
 * @date 2026
 *
 * This example shows:
 * - Using float for performance
 * - Using double for standard precision
 * - Using long double for high precision
 * - Comparing precision differences
 */

#include "areaperipoly.hpp"
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace geometry;

template <typename T> void calculate_with_type(const std::string &type_name) {
  std::cout << "\n--- Using " << type_name << " ---\n";
  std::cout << "Precision: " << std::numeric_limits<T>::digits10
            << " decimal digits\n";

  // Create a triangle with different precision
  std::vector<Point2D<T>> triangle = {
      {T(0.0), T(0.0)},
      {T(1.0), T(0.0)},
      {T(0.5), T(0.866025403784438646763)} // sqrt(3)/2
  };

  auto area = calculate_area_shoelace<T>(triangle);
  auto perimeter = calculate_perimeter<T>(triangle);

  std::cout << std::setprecision(std::numeric_limits<T>::digits10);

  if (area) {
    std::cout << "Area: " << area->value << " square units\n";
  }
  if (perimeter) {
    std::cout << "Perimeter: " << perimeter->value << " units\n";
  }

  // Calculate a circle
  auto circle_area = calculate_circle_area<T>(T(1.0));
  if (circle_area) {
    std::cout << "Unit circle area: " << circle_area->value << "\n";
    std::cout << "Expected (π): " << std::numbers::pi_v<T> << "\n";
  }
}

int main() {
  std::cout << "=== Different Floating-Point Types ===\n";

  calculate_with_type<float>("float");
  calculate_with_type<double>("double");
  calculate_with_type<long double>("long double");

  std::cout << "\n=== Performance Considerations ===\n";
  std::cout << "- float:       Fast, ~7 decimal digits precision\n";
  std::cout << "- double:      Standard, ~15 decimal digits precision\n";
  std::cout << "- long double: Slower, ~18+ decimal digits precision\n";

  std::cout << "\n=== Example Complete ===\n";

  return 0;
}
