/**
 * @file test_basic_types.cpp
 * @brief Unit tests for basic types (Point2D, Area, Perimeter, Coordinate)
 * @author Magpiny
 * @date 2026
 */

#include <concepts>
#include <gtest/gtest.h>
// hello be nice
#include "areaperipoly.hpp"
#include <type_traits>

using namespace geometry;

/**
 * @brief Test fixture for basic type tests
 */
class BasicTypesTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Setup code if needed
  }
};

/**
 * @brief Test Coordinate type construction and comparison
 */
TEST_F(BasicTypesTest, CoordinateConstruction) {
  Coordinate<double> c1{5.0};
  Coordinate<double> c2{5.0};
  Coordinate<double> c3{3.0};

  EXPECT_EQ(c1.value, 5.0);
  EXPECT_EQ(c1, c2);
  EXPECT_NE(c1, c3);
}

/**
 * @brief Test Coordinate arithmetic operations
 */
TEST_F(BasicTypesTest, CoordinateArithmetic) {
  Coordinate<double> c1{5.0};
  Coordinate<double> c2{3.0};

  auto sum = c1 + c2;
  auto diff = c1 - c2;
  auto scaled = c1 * 2.0;

  EXPECT_EQ(sum.value, 8.0);
  EXPECT_EQ(diff.value, 2.0);
  EXPECT_EQ(scaled.value, 10.0);
}

/**
 * @brief Test Area type properties
 */
TEST_F(BasicTypesTest, AreaType) {
  Area<double> a1{25.5};
  Area<double> a2{25.5};
  Area<double> a3{30.0};

  EXPECT_EQ(a1.value, 25.5);
  EXPECT_EQ(a1, a2);
  EXPECT_NE(a1, a3);
  EXPECT_LT(a1, a3);
}

/**
 * @brief Test Perimeter type properties
 */
TEST_F(BasicTypesTest, PerimeterType) {
  Perimeter<double> p1{15.5};
  Perimeter<double> p2{15.5};

  EXPECT_EQ(p1.value, 15.5);
  EXPECT_EQ(p1, p2);
}

/**
 * @brief Test Point2D construction
 */
TEST_F(BasicTypesTest, Point2DConstruction) {
  Point2D<double> p1;
  Point2D<double> p2{3.0, 4.0};

  EXPECT_EQ(p1.x.value, 0.0);
  EXPECT_EQ(p1.y.value, 0.0);
  EXPECT_EQ(p2.x.value, 3.0);
  EXPECT_EQ(p2.y.value, 4.0);
}

/**
 * @brief Test Point2D distance calculation
 */
TEST_F(BasicTypesTest, Point2DDistance) {
  Point2D<double> p1{0.0, 0.0};
  Point2D<double> p2{3.0, 4.0};

  double distance = p1.distance_to(p2);
  EXPECT_DOUBLE_EQ(distance, 5.0);
}

/**
 * @brief Test type traits for strong types
 */
TEST_F(BasicTypesTest, TypeTraits) {
  // Verify types are what we expect
  EXPECT_TRUE((std::is_same_v<decltype(Area<double>{}.value), double>));
  EXPECT_TRUE((std::is_same_v<decltype(Perimeter<float>{}.value), float>));

  // Verify floating point concept
  EXPECT_TRUE(std::floating_point<double>);
  EXPECT_TRUE(std::floating_point<float>);
  EXPECT_FALSE(std::floating_point<int>);
}
