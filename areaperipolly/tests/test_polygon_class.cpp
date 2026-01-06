/**
 * @file test_polygon_class.cpp
 * @brief Unit tests for Polygon class
 * @author Magpiny
 * @date 2026
 */

/**
 * @brief Test fixture for Polygon class
 */

#include <gtest/gtest.h>
// hello
#include "areaperipoly.hpp"

using namespace geometry;

class PolygonClassTest : public ::testing::Test {
protected:
  std::vector<Point2D<double>> valid_vertices;
  std::vector<Point2D<double>> invalid_vertices;

  void SetUp() override {
    valid_vertices = {{0.0, 0.0}, {4.0, 0.0}, {4.0, 3.0}, {0.0, 3.0}};

    invalid_vertices = {{0.0, 0.0}, {1.0, 1.0}};
  }
};

/**
 * @brief Test Polygon construction and validation
 */
TEST_F(PolygonClassTest, Construction) {
  Polygon poly(valid_vertices);

  EXPECT_TRUE(poly.is_valid());
  EXPECT_EQ(poly.vertex_count(), 4);
}

/**
 * @brief Test invalid Polygon
 */
TEST_F(PolygonClassTest, InvalidPolygon) {
  Polygon poly(invalid_vertices);

  EXPECT_FALSE(poly.is_valid());
  EXPECT_EQ(poly.vertex_count(), 2);
}

/**
 * @brief Test Polygon area calculation
 */
TEST_F(PolygonClassTest, AreaCalculation) {
  Polygon poly(valid_vertices);
  auto area = poly.area();

  ASSERT_TRUE(area.has_value());
  EXPECT_DOUBLE_EQ(area->value, 12.0);
}

/**
 * @brief Test Polygon perimeter calculation
 */
TEST_F(PolygonClassTest, PerimeterCalculation) {
  Polygon poly(valid_vertices);
  auto perimeter = poly.perimeter();

  ASSERT_TRUE(perimeter.has_value());
  EXPECT_DOUBLE_EQ(perimeter->value, 14.0);
}

/**
 * @brief Test vertices access
 */
TEST_F(PolygonClassTest, VerticesAccess) {
  Polygon poly(valid_vertices);
  auto vertices = poly.vertices();

  EXPECT_EQ(vertices.size(), 4);
  EXPECT_EQ(vertices[0].x.value, 0.0);
  EXPECT_EQ(vertices[0].y.value, 0.0);
}
