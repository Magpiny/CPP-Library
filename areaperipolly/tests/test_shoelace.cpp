/**
 * @file test_shoelace.cpp
 * @brief Unit tests for Shoelace theorem implementation
 * @author Magpiny
 * @date 2026
 */

/**
 * @brief Test fixture for Shoelace algorithm tests
 *
 */

#include <gtest/gtest.h>
// be nice
#include "areaperipoly.hpp"

using namespace geometry;

class ShoelaceTest : public ::testing::Test {
protected:
  std::vector<Point2D<double>> triangle;
  std::vector<Point2D<double>> square;
  std::vector<Point2D<double>> pentagon;

  void SetUp() override {
    // Right triangle with base=4, height=3
    triangle = {{0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}};

    // Unit square
    square = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}};

    // Regular pentagon (approximate)
    pentagon = {{0.0, 0.0}, {5.0, 0.0}, {6.0, 3.0}, {3.0, 5.0}, {-1.0, 3.0}};
  }
};

/**
 * @brief Test triangle area calculation
 */
TEST_F(ShoelaceTest, TriangleArea) {
  auto area = calculate_area_shoelace(triangle);

  ASSERT_TRUE(area.has_value());
  EXPECT_DOUBLE_EQ(area->value, 6.0); // (4 * 3) / 2 = 6
}

/**
 * @brief Test square area calculation
 */
TEST_F(ShoelaceTest, SquareArea) {
  auto area = calculate_area_shoelace(square);

  ASSERT_TRUE(area.has_value());
  EXPECT_DOUBLE_EQ(area->value, 1.0);
}

/**
 * @brief Test pentagon area calculation
 */
TEST_F(ShoelaceTest, PentagonArea) {
  auto area = calculate_area_shoelace(pentagon);

  ASSERT_TRUE(area.has_value());
  EXPECT_GT(area->value, 0.0);
}

/**
 * @brief Test with invalid polygon (less than 3 vertices)
 */
TEST_F(ShoelaceTest, InvalidPolygon) {
  std::vector<Point2D<double>> invalid = {{0.0, 0.0}, {1.0, 1.0}};

  auto area = calculate_area_shoelace(invalid);
  EXPECT_FALSE(area.has_value());
}

/**
 * @brief Test clockwise vs counter-clockwise ordering
 */
TEST_F(ShoelaceTest, WindingOrder) {
  std::vector<Point2D<double>> ccw = {{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}};

  std::vector<Point2D<double>> cw = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}};

  auto area_ccw = calculate_area_shoelace(ccw);
  auto area_cw = calculate_area_shoelace(cw);

  ASSERT_TRUE(area_ccw.has_value());
  ASSERT_TRUE(area_cw.has_value());
  EXPECT_DOUBLE_EQ(area_ccw->value, area_cw->value);
}

/**
 * @brief Test with different floating point types
 */
TEST_F(ShoelaceTest, DifferentFloatTypes) {
  std::vector<geometry::Point2D<>> triangle_f = {
      {0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}};

  auto area = calculate_area_shoelace<double>(triangle_f);
  ASSERT_TRUE(area.has_value());
  EXPECT_DOUBLE_EQ(area->value, 6.0);
}
