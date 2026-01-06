
/**
 * @file 06_interactive_calculator.cpp
 * @brief Interactive polygon calculator
 * @author Examples
 * @date 2026
 *
 * This example provides:
 * - Interactive command-line interface
 * - User input handling
 * - Multiple calculation modes
 * - Menu-driven navigation
 */

#include "areaperipoly.hpp"
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace geometry;

void clear_input() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void custom_polygon_calculator() {
  std::cout << "\n=== Custom Polygon Calculator ===\n";
  std::cout << "Enter the number of vertices (minimum 3): ";

  size_t num_vertices;
  std::cin >> num_vertices;

  if (num_vertices < 3) {
    std::cout << "Error: Need at least 3 vertices!\n";
    clear_input();
    return;
  }

  std::vector<Point2D<double>> vertices;
  vertices.reserve(num_vertices);

  std::cout << "\nEnter coordinates for each vertex (x y):\n";
  for (size_t i = 0; i < num_vertices; ++i) {
    double x, y;
    std::cout << "Vertex " << (i + 1) << ": ";
    std::cin >> x >> y;
    vertices.emplace_back(x, y);
  }

  auto area = calculate_area_shoelace(vertices);
  auto perimeter = calculate_perimeter(vertices);

  std::cout << "\n--- Results ---\n";
  std::cout << std::fixed << std::setprecision(4);

  if (area) {
    std::cout << "Area: " << area->value << " square units\n";
  }
  if (perimeter) {
    std::cout << "Perimeter: " << perimeter->value << " units\n";
  }
}

void regular_polygon_calculator() {
  std::cout << "\n=== Regular Polygon Calculator ===\n";
  std::cout << "Enter number of sides: ";

  size_t sides;
  std::cin >> sides;

  std::cout << "Enter side length: ";
  double length;
  std::cin >> length;

  auto area = calculate_regular_polygon_area(sides, length);
  auto perimeter = calculate_regular_polygon_perimeter(sides, length);

  std::cout << "\n--- Results ---\n";
  std::cout << std::fixed << std::setprecision(4);

  if (area && perimeter) {
    std::cout << "Area: " << area->value << " square units\n";
    std::cout << "Perimeter: " << perimeter->value << " units\n";
  } else {
    std::cout << "Error: Invalid input!\n";
  }
}

void rectangle_calculator() {
  std::cout << "\n=== Rectangle Calculator ===\n";
  std::cout << "Enter width: ";
  double width;
  std::cin >> width;

  std::cout << "Enter height: ";
  double height;
  std::cin >> height;

  auto area = calculate_rectangle_area(width, height);
  auto perimeter = calculate_rectangle_perimeter(width, height);

  std::cout << "\n--- Results ---\n";
  std::cout << std::fixed << std::setprecision(4);

  if (area && perimeter) {
    std::cout << "Area: " << area->value << " square units\n";
    std::cout << "Perimeter: " << perimeter->value << " units\n";
  } else {
    std::cout << "Error: Invalid dimensions!\n";
  }
}

void circle_calculator() {
  std::cout << "\n=== Circle Calculator ===\n";
  std::cout << "Enter radius: ";
  double radius;
  std::cin >> radius;

  auto area = calculate_circle_area(radius);
  auto circumference = calculate_circle_circumference(radius);

  std::cout << "\n--- Results ---\n";
  std::cout << std::fixed << std::setprecision(4);

  if (area && circumference) {
    std::cout << "Area: " << area->value << " square units\n";
    std::cout << "Circumference: " << circumference->value << " units\n";
  } else {
    std::cout << "Error: Invalid radius!\n";
  }
}

void show_menu() {
  std::cout << "\n╔════════════════════════════════════════╗\n";
  std::cout << "║  Polygon Geometry Calculator           ║\n";
  std::cout << "╠════════════════════════════════════════╣\n";
  std::cout << "║  1. Custom Polygon                     ║\n";
  std::cout << "║  2. Regular Polygon                    ║\n";
  std::cout << "║  3. Rectangle                          ║\n";
  std::cout << "║  4. Circle                             ║\n";
  std::cout << "║  5. Exit                               ║\n";
  std::cout << "╚════════════════════════════════════════╝\n";
  std::cout << "Choose an option: ";
}

int main() {
  std::cout << "=== Interactive Polygon Calculator ===\n";
  std::cout << "Calculate areas and perimeters of various shapes\n";

  while (true) {
    show_menu();

    int choice;
    std::cin >> choice;

    if (!std::cin) {
      clear_input();
      std::cout << "Invalid input! Please enter a number.\n";
      continue;
    }

    switch (choice) {
    case 1:
      custom_polygon_calculator();
      break;
    case 2:
      regular_polygon_calculator();
      break;
    case 3:
      rectangle_calculator();
      break;
    case 4:
      circle_calculator();
      break;
    case 5:
      std::cout << "\nThank you for using Polygon Calculator!\n";
      return 0;
    default:
      std::cout << "Invalid option! Please choose 1-5.\n";
    }

    std::cout << "\nPress Enter to continue...";
    clear_input();
    std::cin.get();
  }

  return 0;
}
