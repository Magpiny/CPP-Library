/**
 * @file 09_compile_time_examples.cpp
 * @brief Compile-time polygon calculations
 * @author Magpiny
 * @date 2026
 *
 * This example demonstrates:
 * - Compile-time area calculations
 * - constexpr polygon creation
 * - Zero runtime overhead
 * - Template metaprogramming applications
 */

#include "areaperipoly.hpp"
#include <array>
#include <iomanip>
#include <iostream>

using namespace geometry;

// Compile-time triangle area calculation
consteval auto compile_time_triangle_area() {
  constexpr std::array<Point2D<double>, 3> triangle = {
      {{0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}}};

  constexpr auto area = calculate_area_shoelace<double>(triangle);
  return area->value;
}

// Compile-time square area calculation
consteval auto compile_time_square_area(double side) {
  std::array<Point2D<double>, 4> square = {
      {{0.0, 0.0}, {side, 0.0}, {side, side}, {0.0, side}}};

  auto area = calculate_area_shoelace<double>(square);
  return area->value;
}

// Compile-time perimeter calculation
consteval auto compile_time_perimeter() {
  constexpr std::array<Point2D<double>, 4> square = {
      {{0.0, 0.0}, {5.0, 0.0}, {5.0, 5.0}, {0.0, 5.0}}};

  constexpr auto perim = calculate_perimeter<double>(square);
  return perim->value;
}

// Template for compile-time validation
template <double Expected, double Actual>
consteval bool validate_compile_time() {
  return (Expected - Actual < 0.0001) && (Actual - Expected < 0.0001);
}

int main() {
  std::cout << "=== Compile-Time Examples ===\n";
  std::cout << std::fixed << std::setprecision(4);

  std::cout << "\n--- Compile-Time Calculations ---\n";
  std::cout
      << "These values are calculated at compile time (zero runtime cost):\n\n";

  // Triangle area (calculated at compile time)
  constexpr double triangle_area = compile_time_triangle_area();
  std::cout << "Triangle area (compile-time): " << triangle_area << "\n";
  static_assert(triangle_area == 6.0, "Triangle area should be 6.0");

  // Square area (calculated at compile time)
  constexpr double square_area = compile_time_square_area(5.0);
  std::cout << "Square area (compile-time): " << square_area << "\n";
  static_assert(square_area == 25.0, "Square area should be 25.0");

  // Perimeter (calculated at compile time)
  constexpr double perimeter = compile_time_perimeter();
  std::cout << "Square perimeter (compile-time): " << perimeter << "\n";
  static_assert(perimeter == 20.0, "Square perimeter should be 20.0");

  // Coordinate operations at compile time
  constexpr Coordinate<double> c1{5.0};
  constexpr Coordinate<double> c2{3.0};
  constexpr auto sum = c1 + c2;
  std::cout << "\nCoordinate sum (compile-time): " << sum.value << "\n";
  static_assert(sum.value == 8.0);

  // Point distance at compile time
  constexpr Point2D<double> p1{0.0, 0.0};
  constexpr Point2D<double> p2{3.0, 4.0};
  constexpr double distance = p1.distance_to(p2);
  std::cout << "Point distance (compile-time): " << distance << "\n";
  static_assert(distance == 5.0);

  std::cout << "\n--- Benefits of Compile-Time Calculations ---\n";
  std::cout << "✓ Zero runtime overhead\n";
  std::cout << "✓ Errors caught at compile time\n";
  std::cout << "✓ Results embedded in binary\n";
  std::cout << "✓ Can be used in other constexpr contexts\n";
  std::cout << "✓ Perfect for lookup tables and constants\n";

  std::cout << "\n--- Runtime Comparison ---\n";
  std::cout << "Runtime calculation (for comparison):\n";

  std::vector<Point2D<double>> runtime_triangle = {
      {0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}};

  auto runtime_area = calculate_area_shoelace(runtime_triangle);
  std::cout << "Triangle area (runtime): " << runtime_area->value << "\n";
  std::cout << "\nBoth produce the same result, but compile-time is free!\n";

  std::cout << "\n=== Example Complete ===\n";

  return 0;
}
