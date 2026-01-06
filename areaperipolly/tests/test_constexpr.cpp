/**
 * @file test_constexpr.cpp
 * @brief Tests for compile-time evaluation capabilities
 * @author Magpiny
 * @date 2026
 */

/**
 * @brief Test compile-time triangle area calculation
 */

#include "areaperipoly.hpp"
#include <gtest/gtest.h>

using namespace geometry;

TEST(ConstexprTest, CompileTimeTriangleArea) {
  constexpr std::array<Point2D<double>, 3> triangle = {
      {{0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}}};

  constexpr auto area = calculate_area_shoelace<double>(triangle);
  static_assert(area.has_value());
  static_assert(area->value == 6.0);

  EXPECT_DOUBLE_EQ(area->value, 6.0);
}

/**
 * @brief Test compile-time perimeter calculation
 */
TEST(ConstexprTest, CompileTimePerimeter) {
  constexpr std::array<Point2D<double>, 4> square = {
      {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};

  constexpr auto perimeta = calculate_perimeter<double>(square);
  static_assert(perimeta.has_value());

  EXPECT_DOUBLE_EQ(perimeta->value, 4.0);
}

/**
 * @brief Test compile-time coordinate operations
 */
TEST(ConstexprTest, CompileTimeCoordinates) {
  constexpr Coordinate<double> c1{5.0};
  constexpr Coordinate<double> c2{3.0};
  constexpr auto sum = c1 + c2;

  static_assert(sum.value == 8.0);
  EXPECT_DOUBLE_EQ(sum.value, 8.0);
}
