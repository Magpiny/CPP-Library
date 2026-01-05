/**
 * @file areaperipolly.hpp
 * @brief Modern C++26 library for calculating area and perimeter of polygons
 * @author Magpiny
 * @date 2026
 */

#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <numbers>
#include <optional>
#include <ranges>
#include <span>
#include <vector>

namespace geometry {

/**
 * @brief coordinate value type
 */
template <std::floating_point T = double> struct Coordinate {
  T value{};

  constexpr explicit Coordinate(T v = T{}) noexcept : value(v) {}
  constexpr auto operator<=>(const Coordinate &) const noexcept = default;
  constexpr Coordinate operator+(const Coordinate &other) const noexcept {
    return Coordinate{value + other.value};
  }
  constexpr Coordinate operator-(const Coordinate &other) const noexcept {
    return Coordinate{value - other.value};
  }
  constexpr Coordinate operator*(T scalar) const noexcept {
    return Coordinate{value * scalar};
  }
};

/**
 * @brief area type in square units
 */
template <std::floating_point T = double> struct Area {
  T value{};

  constexpr explicit Area(T v = T{}) noexcept : value(v) {}
  constexpr auto operator<=>(const Area &) const noexcept = default;
};

/**
 * @brief Strong type for representing perimeter in linear units
 */
template <std::floating_point T = double> struct Perimeter {
  T value{};

  constexpr explicit Perimeter(T v = T{}) noexcept : value(v) {}
  constexpr auto operator<=>(const Perimeter &) const noexcept = default;
};

/**
 * @brief Represents a 2D point with strong typing
 * @tparam T The floating point type for coordinates
 */
template <std::floating_point T = double> struct Point2D {
  Coordinate<T> x{};
  Coordinate<T> y{};

  constexpr Point2D() noexcept = default;
  constexpr Point2D(T x_val, T y_val) noexcept
      : x(Coordinate<T>{x_val}), y(Coordinate<T>{y_val}) {}

  constexpr auto operator<=>(const Point2D &) const noexcept = default;

  /**
   * @brief Calculate Euclidean distance to another point
   * @param other The other point
   * @return Distance between the two points
   */
  [[nodiscard]] constexpr T distance_to(const Point2D &other) const noexcept {
    T dx = other.x.value - x.value;
    T dy = other.y.value - y.value;
    return std::sqrt(dx * dx + dy * dy);
  }
};

/**
 * @brief Concept for a valid polygon (at least 3 vertices)
 */
template <typename R>
concept PolygonRange = std::ranges::random_access_range<R> && requires(R r) {
  { std::ranges::size(r) } -> std::convertible_to<std::size_t>;
  { *std::ranges::begin(r) } -> std::convertible_to<Point2D<>>;
};

/**
 * @brief Calculate the area of a polygon using the Shoelace theorem
 * @tparam T The floating point type for calculations
 * @param vertices The vertices of the polygon in order (clockwise or
 * counter-clockwise)
 * @return Area of the polygon, or std::nullopt if invalid
 *
 * The Shoelace theorem (also known as the surveyor's formula) calculates the
 * area of a simple polygon given the coordinates of its vertices: Area = 0.5 *
 * |Σ(x_i * y_{i+1} - x_{i+1} * y_i)|
 */
template <std::floating_point T = double, PolygonRange R>
  requires std::same_as<std::ranges::range_value_t<R>, Point2D<T>>
[[nodiscard]] constexpr std::optional<Area<T>>
calculate_area_shoelace(const R &vertices) noexcept {
  const std::size_t n = std::ranges::size(vertices);

  if (n < 3) {
    return std::nullopt;
  }

  T sum{};

  for (std::size_t i = 0; i < n; ++i) {
    const auto &current = vertices[i];
    const auto &next = vertices[(i + 1) % n];

    sum += current.x.value * next.y.value;
    sum -= next.x.value * current.y.value;
  }

  return Area<T>{std::abs(sum) / T{2}};
}

/**
 * @brief Calculate the perimeter of a polygon
 * @tparam T The floating point type for calculations
 * @param vertices The vertices of the polygon in order
 * @return Perimeter of the polygon, or std::nullopt if invalid
 */
template <std::floating_point T = double, PolygonRange R>
  requires std::same_as<std::ranges::range_value_t<R>, Point2D<T>>
[[nodiscard]] constexpr std::optional<Perimeter<T>>
calculate_perimeter(const R &vertices) noexcept {
  const std::size_t n = std::ranges::size(vertices);

  if (n < 3) {
    return std::nullopt;
  }

  T total{};

  for (std::size_t i = 0; i < n; ++i) {
    const auto &current = vertices[i];
    const auto &next = vertices[(i + 1) % n];
    total += current.distance_to(next);
  }

  return Perimeter<T>{total};
}

/**
 * @brief Calculate area of a regular polygon (all sides equal, all angles
 * equal)
 * @tparam T The floating point type for calculations
 * @param num_sides Number of sides (must be >= 3)
 * @param side_length Length of each side
 * @return Area of the regular polygon, or std::nullopt if invalid
 *
 * Formula: Area = (n * s²) / (4 * tan(π/n))
 * where n = number of sides, s = side length
 */
template <std::floating_point T = double>
[[nodiscard]] constexpr std::optional<Area<T>>
calculate_regular_polygon_area(std::size_t num_sides, T side_length) noexcept {

  if (num_sides < 3 || side_length <= T{}) {
    return std::nullopt;
  }

  const T n = static_cast<T>(num_sides);
  const T angle = std::numbers::pi_v<T> / n;
  const T area_val = (n * side_length * side_length) / (T{4} * std::tan(angle));

  return Area<T>{area_val};
}

/**
 * @brief Calculate perimeter of a regular polygon
 * @tparam T The floating point type for calculations
 * @param num_sides Number of sides (must be >= 3)
 * @param side_length Length of each side
 * @return Perimeter of the regular polygon, or std::nullopt if invalid
 */
template <std::floating_point T = double>
[[nodiscard]] constexpr std::optional<Perimeter<T>>
calculate_regular_polygon_perimeter(std::size_t num_sides,
                                    T side_length) noexcept {

  if (num_sides < 3 || side_length <= T{}) {
    return std::nullopt;
  }

  return Perimeter<T>{static_cast<T>(num_sides) * side_length};
}

/**
 * @brief Calculate area of a triangle using vertices
 * @tparam T The floating point type for calculations
 * @param p1 First vertex
 * @param p2 Second vertex
 * @param p3 Third vertex
 * @return Area of the triangle
 */
template <std::floating_point T = double>
[[nodiscard]] constexpr Area<T>
calculate_triangle_area(const Point2D<T> &p1, const Point2D<T> &p2,
                        const Point2D<T> &p3) noexcept {

  const std::array vertices = {p1, p2, p3};
  return calculate_area_shoelace<T>(vertices).value();
}

/**
 * @brief Calculate area of a rectangle
 * @tparam T The floating point type for calculations
 * @param width Rectangle width
 * @param height Rectangle height
 * @return Area of the rectangle, or std::nullopt if invalid dimensions
 */
template <std::floating_point T = double>
[[nodiscard]] constexpr std::optional<Area<T>>
calculate_rectangle_area(T width, T height) noexcept {

  if (width <= T{} || height <= T{}) {
    return std::nullopt;
  }

  return Area<T>{width * height};
}

/**
 * @brief Calculate perimeter of a rectangle
 * @tparam T The floating point type for calculations
 * @param width Rectangle width
 * @param height Rectangle height
 * @return Perimeter of the rectangle, or std::nullopt if invalid dimensions
 */
template <std::floating_point T = double>
[[nodiscard]] constexpr std::optional<Perimeter<T>>
calculate_rectangle_perimeter(T width, T height) noexcept {

  if (width <= T{} || height <= T{}) {
    return std::nullopt;
  }

  return Perimeter<T>{T{2} * (width + height)};
}

/**
 * @brief Calculate area of a circle
 * @tparam T The floating point type for calculations
 * @param radius Circle radius
 * @return Area of the circle, or std::nullopt if invalid radius
 */
template <std::floating_point T = double>
[[nodiscard]] constexpr std::optional<Area<T>>
calculate_circle_area(T radius) noexcept {
  if (radius <= T{}) {
    return std::nullopt;
  }

  return Area<T>{std::numbers::pi_v<T> * radius * radius};
}

/**
 * @brief Calculate circumference of a circle
 * @tparam T The floating point type for calculations
 * @param radius Circle radius
 * @return Circumference of the circle, or std::nullopt if invalid radius
 */
template <std::floating_point T = double>
[[nodiscard]] constexpr std::optional<Perimeter<T>>
calculate_circle_circumference(T radius) noexcept {
  if (radius <= T{}) {
    return std::nullopt;
  }

  return Perimeter<T>{T{2} * std::numbers::pi_v<T> * radius};
}

/**
 * @brief Polygon class for storing and analyzing polygon properties
 * @tparam T The floating point type for calculations
 */
template <std::floating_point T = double> class Polygon {
public:
  /**
   * @brief Construct a polygon from vertices
   * @param vertices Vector of vertices in order
   */
  explicit Polygon(std::vector<Point2D<T>> vertices)
      : vertices_(std::move(vertices)) {}

  /**
   * @brief Get the vertices of the polygon
   * @return Span of vertices
   */
  [[nodiscard]] constexpr std::span<const Point2D<T>>
  vertices() const noexcept {
    return vertices_;
  }

  /**
   * @brief Calculate the area using the Shoelace theorem
   * @return Area of the polygon, or std::nullopt if invalid
   */
  [[nodiscard]] constexpr std::optional<Area<T>> area() const noexcept {
    return calculate_area_shoelace<T>(vertices_);
  }

  /**
   * @brief Calculate the perimeter
   * @return Perimeter of the polygon, or std::nullopt if invalid
   */
  [[nodiscard]] constexpr std::optional<Perimeter<T>>
  perimeter() const noexcept {
    return calculate_perimeter<T>(vertices_);
  }

  /**
   * @brief Get the number of vertices
   * @return Number of vertices
   */
  [[nodiscard]] constexpr std::size_t vertex_count() const noexcept {
    return vertices_.size();
  }

  /**
   * @brief Check if the polygon is valid (at least 3 vertices)
   * @return True if valid, false otherwise
   */
  [[nodiscard]] constexpr bool is_valid() const noexcept {
    return vertices_.size() >= 3;
  }

private:
  std::vector<Point2D<T>> vertices_;
};

} // namespace geometry
