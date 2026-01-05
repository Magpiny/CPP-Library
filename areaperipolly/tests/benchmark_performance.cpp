/**
 * @file benchmark_performance.cpp
 * @brief Performance benchmarks for polygon geometry library
 * @author Magpiny
 * @date 2026
 */

#include "areaperipoly.hpp"
#include <array>
#include <benchmark/benchmark.h>
#include <random>
#include <vector>

using namespace geometry;

/**
 * @brief Generate random polygon vertices
 * @param n Number of vertices
 * @param seed Random seed
 * @return Vector of random points
 */
std::vector<Point2D<double>> generate_random_polygon(size_t n,
                                                     unsigned seed = 42) {
  std::mt19937 gen(seed);
  std::uniform_real_distribution<double> dis(0.0, 1000.0);

  std::vector<Point2D<double>> vertices;
  vertices.reserve(n);

  // Generate points on a circle to ensure valid polygon
  for (size_t i = 0; i < n; ++i) {
    double angle = 2.0 * std::numbers::pi * i / n;
    double radius = 100.0 + dis(gen) * 0.1; // Add slight variation
    vertices.emplace_back(radius * std::cos(angle), radius * std::sin(angle));
  }

  return vertices;
}

/**
 * @brief Benchmark: Triangle area calculation using Shoelace
 */
static void BM_TriangleArea(benchmark::State &state) {
  std::vector<Point2D<double>> triangle = {{0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}};

  for (auto _ : state) {
    auto area = calculate_area_shoelace(triangle);
    benchmark::DoNotOptimize(area);
  }

  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_TriangleArea);

/**
 * @brief Benchmark: Square area calculation
 */
static void BM_SquareArea(benchmark::State &state) {
  std::vector<Point2D<double>> square = {
      {0.0, 0.0}, {10.0, 0.0}, {10.0, 10.0}, {0.0, 10.0}};

  for (auto _ : state) {
    auto area = calculate_area_shoelace(square);
    benchmark::DoNotOptimize(area);
  }

  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_SquareArea);

/**
 * @brief Benchmark: Polygon area with varying vertex counts
 */
static void BM_PolygonArea_VariableSize(benchmark::State &state) {
  auto vertices = generate_random_polygon(state.range(0));

  for (auto _ : state) {
    auto area = calculate_area_shoelace(vertices);
    benchmark::DoNotOptimize(area);
  }

  state.SetComplexityN(state.range(0));
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_PolygonArea_VariableSize)
    ->RangeMultiplier(2)
    ->Range(4, 1024)
    ->Complexity();

/**
 * @brief Benchmark: Perimeter calculation with varying vertex counts
 */
static void BM_Perimeter_VariableSize(benchmark::State &state) {
  auto vertices = generate_random_polygon(state.range(0));

  for (auto _ : state) {
    auto perimeter = calculate_perimeter(vertices);
    benchmark::DoNotOptimize(perimeter);
  }

  state.SetComplexityN(state.range(0));
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Perimeter_VariableSize)
    ->RangeMultiplier(2)
    ->Range(4, 1024)
    ->Complexity();

/**
 * @brief Benchmark: Regular polygon area calculation
 */
static void BM_RegularPolygonArea(benchmark::State &state) {
  const size_t sides = state.range(0);
  const double side_length = 5.0;

  for (auto _ : state) {
    auto area = calculate_regular_polygon_area(sides, side_length);
    benchmark::DoNotOptimize(area);
  }

  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_RegularPolygonArea)->Arg(3)->Arg(6)->Arg(8)->Arg(12)->Arg(100);

/**
 * @brief Benchmark: Rectangle area calculation
 */
static void BM_RectangleArea(benchmark::State &state) {
  for (auto _ : state) {
    auto area = calculate_rectangle_area(10.0, 5.0);
    benchmark::DoNotOptimize(area);
  }

  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_RectangleArea);

/**
 * @brief Benchmark: Circle area calculation
 */
static void BM_CircleArea(benchmark::State &state) {
  for (auto _ : state) {
    auto area = calculate_circle_area(7.5);
    benchmark::DoNotOptimize(area);
  }

  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_CircleArea);

/**
 * @brief Benchmark: Polygon class construction and area
 */
static void BM_PolygonClass(benchmark::State &state) {
  auto vertices = generate_random_polygon(state.range(0));

  for (auto _ : state) {
    Polygon poly(vertices);
    auto area = poly.area();
    benchmark::DoNotOptimize(area);
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_PolygonClass)->RangeMultiplier(2)->Range(4, 256)->Complexity();

/**
 * @brief Benchmark: Point distance calculation
 */
static void BM_PointDistance(benchmark::State &state) {
  Point2D p1{0.0, 0.0};
  Point2D p2{3.0, 4.0};

  for (auto _ : state) {
    auto distance = p1.distance_to(p2);
    benchmark::DoNotOptimize(distance);
  }

  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_PointDistance);

/**
 * @brief Benchmark: Heavy load - Multiple polygons
 */
static void BM_HeavyLoad_MultiplePolygons(benchmark::State &state) {
  const size_t num_polygons = state.range(0);
  std::vector<std::vector<Point2D<double>>> polygons;

  for (size_t i = 0; i < num_polygons; ++i) {
    polygons.push_back(generate_random_polygon(10, i));
  }

  for (auto _ : state) {
    for (const auto &poly : polygons) {
      auto area = calculate_area_shoelace(poly);
      benchmark::DoNotOptimize(area);
    }
  }

  state.SetItemsProcessed(state.iterations() * num_polygons);
}
BENCHMARK(BM_HeavyLoad_MultiplePolygons)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000);

/**
 * @brief Benchmark: Memory intensive - Large vertex count
 */
static void BM_LargePolygon(benchmark::State &state) {
  auto vertices = generate_random_polygon(10000);

  for (auto _ : state) {
    auto area = calculate_area_shoelace(vertices);
    auto perimeter = calculate_perimeter(vertices);
    benchmark::DoNotOptimize(area);
    benchmark::DoNotOptimize(perimeter);
  }

  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_LargePolygon);

/**
 * @brief Benchmark: Float vs Double precision
 */
static void BM_FloatPrecision(benchmark::State &state) {
  std::vector<Point2D<float>> triangle = {
      {0.0f, 0.0f}, {4.0f, 0.0f}, {0.0f, 3.0f}};

  for (auto _ : state) {
    auto area = calculate_area_shoelace<float>(triangle);
    benchmark::DoNotOptimize(area);
  }

  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_FloatPrecision);

/**
 * @brief Benchmark: Double precision
 */
static void BM_DoublePrecision(benchmark::State &state) {
  std::vector<Point2D<double>> triangle = {{0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}};

  for (auto _ : state) {
    auto area = calculate_area_shoelace<double>(triangle);
    benchmark::DoNotOptimize(area);
  }

  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_DoublePrecision);

/**
 * @brief Benchmark: Batch processing with different sizes
 */
static void BM_BatchProcessing(benchmark::State &state) {
  std::vector<std::vector<Point2D<double>>> batch;
  batch.push_back(generate_random_polygon(4));
  batch.push_back(generate_random_polygon(8));
  batch.push_back(generate_random_polygon(16));
  batch.push_back(generate_random_polygon(32));
  batch.push_back(generate_random_polygon(64));

  for (auto _ : state) {
    for (const auto &poly : batch) {
      auto area = calculate_area_shoelace(poly);
      auto perimeter = calculate_perimeter(poly);
      benchmark::DoNotOptimize(area);
      benchmark::DoNotOptimize(perimeter);
    }
  }

  state.SetItemsProcessed(state.iterations() * batch.size());
}
BENCHMARK(BM_BatchProcessing);

/**
 * @brief Benchmark: Worst case - Many small calculations
 */
static void BM_ManySmallCalculations(benchmark::State &state) {
  std::vector<Point2D<double>> triangle = {{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}};

  const size_t iterations_per_loop = 1000;

  for (auto _ : state) {
    for (size_t i = 0; i < iterations_per_loop; ++i) {
      auto area = calculate_area_shoelace(triangle);
      benchmark::DoNotOptimize(area);
    }
  }

  state.SetItemsProcessed(state.iterations() * iterations_per_loop);
}
BENCHMARK(BM_ManySmallCalculations);

// Run the benchmarks
BENCHMARK_MAIN();
