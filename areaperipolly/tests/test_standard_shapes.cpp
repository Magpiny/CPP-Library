/**
 * @file test_standard_shapes.cpp
 * @brief Unit tests for standard shape calculations (rectangles, circles,
 * triangles)
 * @author Magpiny
 * @date 2026
 */

/**
 * @brief Test fixture for standard shapes
 */
class StandardShapesTest : public ::testing::Test {
protected:
  const double pi = 3.14159265358979323846;
};

/**
 * @brief Test rectangle area calculation
 */
TEST_F(StandardShapesTest, RectangleArea) {
  auto area = calculate_rectangle_area(5.0, 3.0);

  ASSERT_TRUE(area.has_value());
  EXPECT_DOUBLE_EQ(area->value, 15.0);
}

/**
 * @brief Test rectangle perimeter calculation
 */
TEST_F(StandardShapesTest, RectanglePerimeter) {
  auto perimeter = calculate_rectangle_perimeter(5.0, 3.0);

  ASSERT_TRUE(perimeter.has_value());
  EXPECT_DOUBLE_EQ(perimeter->value, 16.0);
}

/**
 * @brief Test invalid rectangle dimensions
 */
TEST_F(StandardShapesTest, InvalidRectangle) {
  auto area1 = calculate_rectangle_area(-5.0, 3.0);
  auto area2 = calculate_rectangle_area(5.0, 0.0);

  EXPECT_FALSE(area1.has_value());
  EXPECT_FALSE(area2.has_value());
}

/**
 * @brief Test circle area calculation
 */
TEST_F(StandardShapesTest, CircleArea) {
  auto area = calculate_circle_area(5.0);

  ASSERT_TRUE(area.has_value());
  EXPECT_NEAR(area->value, pi * 25.0, 1e-10);
}

/**
 * @brief Test circle circumference calculation
 */
TEST_F(StandardShapesTest, CircleCircumference) {
  auto circumference = calculate_circle_circumference(7.0);

  ASSERT_TRUE(circumference.has_value());
  EXPECT_NEAR(circumference->value, 2.0 * pi * 7.0, 1e-10);
}

/**
 * @brief Test invalid circle radius
 */
TEST_F(StandardShapesTest, InvalidCircle) {
  auto area = calculate_circle_area(-3.0);
  EXPECT_FALSE(area.has_value());
}

/**
 * @brief Test triangle area from vertices
 */
TEST_F(StandardShapesTest, TriangleFromVertices) {
  Point2D p1{0.0, 0.0};
  Point2D p2{4.0, 0.0};
  Point2D p3{2.0, 3.0};

  auto area = calculate_triangle_area(p1, p2, p3);
  EXPECT_DOUBLE_EQ(area.value, 6.0);
}
