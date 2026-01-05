/**
 * @file test_edge_cases.cpp
 * @brief Edge case and boundary condition tests
 * @author Magpiny
 * @date 2026
 */

/**
 * @brief Test fixture for edge cases
 */
class EdgeCasesTest : public ::testing::Test {};

/**
 * @brief Test with very small values
 */
TEST_F(EdgeCasesTest, VerySmallValues) {
  std::vector<Point2D<double>> tiny_triangle = {
      {0.0, 0.0}, {1e-10, 0.0}, {0.0, 1e-10}};

  auto area = calculate_area_shoelace(tiny_triangle);
  ASSERT_TRUE(area.has_value());
  EXPECT_GT(area->value, 0.0);
}

/**
 * @brief Test with very large values
 */
TEST_F(EdgeCasesTest, VeryLargeValues) {
  std::vector<Point2D<double>> huge_square = {
      {0.0, 0.0}, {1e10, 0.0}, {1e10, 1e10}, {0.0, 1e10}};

  auto area = calculate_area_shoelace(huge_square);
  ASSERT_TRUE(area.has_value());
  EXPECT_DOUBLE_EQ(area->value, 1e20);
}

/**
 * @brief Test with collinear points (degenerate polygon)
 */
TEST_F(EdgeCasesTest, CollinearPoints) {
  std::vector<Point2D<double>> line = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}};

  auto area = calculate_area_shoelace(line);
  ASSERT_TRUE(area.has_value());
  EXPECT_NEAR(area->value, 0.0, 1e-10);
}

/**
 * @brief Test with duplicate points
 */
TEST_F(EdgeCasesTest, DuplicatePoints) {
  std::vector<Point2D<double>> with_dup = {
      {0.0, 0.0}, {1.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}};

  auto area = calculate_area_shoelace(with_dup);
  ASSERT_TRUE(area.has_value());
}

/**
 * @brief Test with self-intersecting polygon
 */
TEST_F(EdgeCasesTest, SelfIntersecting) {
  std::vector<Point2D<double>> bowtie = {
      {0.0, 0.0}, {2.0, 2.0}, {2.0, 0.0}, {0.0, 2.0}};

  auto area = calculate_area_shoelace(bowtie);
  ASSERT_TRUE(area.has_value());
  // Shoelace still works, but area interpretation may be complex
}
