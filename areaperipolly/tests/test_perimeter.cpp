/**
 * @file test_perimeter.cpp
 * @brief Unit tests for perimeter calculations
 * @author Magpiny
 * @date 2026
 */

/**
 * @brief Test fixture for perimeter tests
 */
class PerimeterTest : public ::testing::Test {
protected:
  std::vector<Point2D<double>> square;
  std::vector<Point2D<double>> equilateral_triangle;

  void SetUp() override {
    square = {{0.0, 0.0}, {4.0, 0.0}, {4.0, 4.0}, {0.0, 4.0}};

    equilateral_triangle = {
        {0.0, 0.0}, {2.0, 0.0}, {1.0, 1.732} // approximately sqrt(3)
    };
  }
};

/**
 * @brief Test square perimeter
 */
TEST_F(PerimeterTest, SquarePerimeter) {
  auto perimeter = calculate_perimeter(square);

  ASSERT_TRUE(perimeter.has_value());
  EXPECT_DOUBLE_EQ(perimeter->value, 16.0);
}

/**
 * @brief Test equilateral triangle perimeter
 */
TEST_F(PerimeterTest, EquilateralTrianglePerimeter) {
  auto perimeter = calculate_perimeter(equilateral_triangle);

  ASSERT_TRUE(perimeter.has_value());
  EXPECT_NEAR(perimeter->value, 6.0, 0.01);
}

/**
 * @brief Test invalid perimeter calculation
 */
TEST_F(PerimeterTest, InvalidPerimeter) {
  std::vector<Point2D<double>> invalid = {{0.0, 0.0}};
  auto perimeter = calculate_perimeter(invalid);

  EXPECT_FALSE(perimeter.has_value());
}
