/**
 * @file test_regular_polygons.cpp
 * @brief Unit tests for regular polygon calculations
 * @author Magpiny
 * @date 2026
 */

/**
 * @brief Test fixture for regular polygon tests
 */
class RegularPolygonTest : public ::testing::Test {
protected:
  const double tolerance = 1e-10;
};

/**
 * @brief Test equilateral triangle (regular 3-gon)
 */
TEST_F(RegularPolygonTest, EquilateralTriangle) {
  auto area = calculate_regular_polygon_area(3, 2.0);
  auto perimeter = calculate_regular_polygon_perimeter(3, 2.0);

  ASSERT_TRUE(area.has_value());
  ASSERT_TRUE(perimeter.has_value());

  EXPECT_NEAR(area->value, 1.732, 0.001); // sqrt(3) ≈ 1.732
  EXPECT_DOUBLE_EQ(perimeter->value, 6.0);
}

/**
 * @brief Test square (regular 4-gon)
 */
TEST_F(RegularPolygonTest, Square) {
  auto area = calculate_regular_polygon_area(4, 5.0);
  auto perimeter = calculate_regular_polygon_perimeter(4, 5.0);

  ASSERT_TRUE(area.has_value());
  ASSERT_TRUE(perimeter.has_value());

  EXPECT_DOUBLE_EQ(area->value, 25.0);
  EXPECT_DOUBLE_EQ(perimeter->value, 20.0);
}

/**
 * @brief Test regular hexagon
 */
TEST_F(RegularPolygonTest, Hexagon) {
  auto area = calculate_regular_polygon_area(6, 1.0);
  auto perimeter = calculate_regular_polygon_perimeter(6, 1.0);

  ASSERT_TRUE(area.has_value());
  ASSERT_TRUE(perimeter.has_value());

  EXPECT_NEAR(area->value, 2.598, 0.001); // 3*sqrt(3)/2 ≈ 2.598
  EXPECT_DOUBLE_EQ(perimeter->value, 6.0);
}

/**
 * @brief Test invalid regular polygon (less than 3 sides)
 */
TEST_F(RegularPolygonTest, InvalidSideCount) {
  auto area = calculate_regular_polygon_area(2, 5.0);
  EXPECT_FALSE(area.has_value());
}

/**
 * @brief Test invalid side length (negative)
 */
TEST_F(RegularPolygonTest, NegativeSideLength) {
  auto area = calculate_regular_polygon_area(5, -1.0);
  EXPECT_FALSE(area.has_value());
}
