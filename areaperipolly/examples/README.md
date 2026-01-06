# AreaPeriPoly Examples 📚

Comprehensive collection of examples demonstrating the AreaPeriPoly library's features and real-world applications.

## 📋 Table of Contents

- [Overview](#overview)
- [Building Examples](#building-examples)
- [Running Examples](#running-examples)
- [Example Descriptions](#example-descriptions)
- [Quick Start Guide](#quick-start-guide)
- [Advanced Topics](#advanced-topics)

## 🎯 Overview

This directory contains 10 example programs covering everything from basic usage to advanced performance optimization and real-world applications.

### Example Categories

| Category | Examples | Description |
|----------|----------|-------------|
| **Beginner** | 01-04 | Basic usage, types, and error handling |
| **Intermediate** | 05-06 | Real-world applications |
| **Advanced** | 07-10 | Performance, batch processing, visualization |

### Prerequisites

- C++26 compliant compiler (GCC 15+, Clang 18+, MSVC 2024+)
- CMake 4.2+
- Built AreaPeriPoly library

## 🔨 Building Examples

### Build All Examples

```bash
# From project root
cmake -B build -DPOLYGON_GEOMETRY_BUILD_EXAMPLES=ON
cmake --build build

# Or use the specific target
cmake --build build --target build_all_examples
```

### Build Specific Example

```bash
# Build just one example
cmake --build build --target 01_basic_usage
```

### Build Configuration

```bash
# Debug build for learning
cmake -B build-debug \
    -DCMAKE_BUILD_TYPE=Debug \
    -DPOLYGON_GEOMETRY_BUILD_EXAMPLES=ON

# Optimized release build
cmake -B build-release \
    -DCMAKE_BUILD_TYPE=Release \
    -DPOLYGON_GEOMETRY_BUILD_EXAMPLES=ON
```

## 🚀 Running Examples

### Run All Examples

```bash
# Run all examples sequentially
make run_all_examples

# Or run individually
./build/examples/01_basic_usage
./build/examples/02_polygon_class
# ... etc
```

### Run Specific Example

```bash
# Using make target
make run_01_basic_usage

# Or directly
./build/examples/01_basic_usage
```

### Run with Output Redirection

```bash
# Save output to file
./build/examples/05_real_world_land_surveying > survey_report.txt

# Run and view with pager
./build/examples/08_batch_processing | less
```

## 📖 Example Descriptions

### 01. Basic Usage (`01_basic_usage.cpp`)

**Difficulty:** 🟢 Beginner  
**Topics:** Fundamentals, Simple shapes, Basic API

The perfect starting point! This example demonstrates:

- Creating simple polygons (triangles, squares, pentagons)
- Using the Shoelace theorem for area calculations
- Calculating perimeters
- Working with regular polygons
- Basic shapes (rectangles, circles)

**Key Functions Covered:**
- `calculate_area_shoelace()`
- `calculate_perimeter()`
- `calculate_regular_polygon_area()`
- `calculate_rectangle_area()`
- `calculate_circle_area()`

**Sample Output:**
```
=== AreaPeriPoly: Basic Usage ===

1. Triangle Example
   Creating a right triangle with base=4, height=3
   Area: 6.00 square units
   Perimeter: 12.00 units
   Expected area: 6.00 (base × height / 2)
```

**What You'll Learn:**
- How to create polygon vertices
- Basic area and perimeter calculations
- Using different shape functions
- Interpreting results

---

### 02. Polygon Class (`02_polygon_class.cpp`)

**Difficulty:** 🟢 Beginner  
**Topics:** OOP interface, Validation, Properties

Learn the object-oriented interface of the library.

**Features Demonstrated:**
- Creating `Polygon` objects
- Accessing polygon properties
- Validation with `is_valid()`
- Querying vertex count
- Working with vertex data

**Key Concepts:**
- Polygon validation (minimum 3 vertices)
- Property queries (area, perimeter, vertex count)
- Vertex access via `std::span`
- Error detection for invalid polygons

**Sample Output:**
```
--- Regular Hexagon ---
Valid: Yes
Vertices: 6
Area: 10.39 square units
Perimeter: 12.00 units
```

**What You'll Learn:**
- Using the Polygon class
- Object-oriented approach
- Validation before calculations
- Accessing polygon data

---

### 03. Different Types (`03_different_types.cpp`)

**Difficulty:** 🟡 Intermediate  
**Topics:** Template usage, Precision, Performance

Explore using different floating-point types for various needs.

**Demonstrates:**
- Using `float` for performance
- Using `double` for standard precision
- Using `long double` for high precision
- Comparing precision differences
- Performance vs accuracy tradeoffs

**Precision Comparison:**
| Type | Precision | Speed | Use Case |
|------|-----------|-------|----------|
| `float` | ~7 digits | Fastest | Real-time graphics |
| `double` | ~15 digits | Standard | General purpose |
| `long double` | ~18+ digits | Slower | Scientific computing |

**Sample Output:**
```
--- Using float ---
Precision: 6 decimal digits
Area: 0.433013 square units
Unit circle area: 3.14159

--- Using double ---
Precision: 15 decimal digits
Area: 0.433012701892219 square units
Unit circle area: 3.14159265358979
```

**What You'll Learn:**
- Template parameter usage
- Precision requirements for different applications
- Performance characteristics
- When to use each type

---

### 04. Error Handling (`04_error_handling.cpp`)

**Difficulty:** 🟢 Beginner  
**Topics:** std::optional, Validation, Robust code

Master robust error handling patterns.

**Covers:**
- Using `std::optional` for error checking
- Validating inputs before calculations
- Handling edge cases gracefully
- Best practices for production code

**Error Scenarios:**
- Polygons with < 3 vertices
- Empty vertex lists
- Invalid regular polygon parameters (< 3 sides)
- Negative or zero dimensions
- Invalid radii

**Sample Output:**
```
Trying: Valid triangle
Vertices: 3
✓ Success! Area = 0.50 square units

Trying: Polygon with only 2 vertices
Vertices: 2
✗ Failed! Invalid polygon (need at least 3 vertices)
```

**What You'll Learn:**
- Proper error handling with `std::optional`
- Input validation patterns
- Defensive programming
- User-friendly error messages

---

### 05. Real-World Land Surveying (`05_real_world_land_surveying.cpp`)

**Difficulty:** 🟡 Intermediate  
**Topics:** Real-world application, Unit conversion, Reports

A practical application for property measurement and land surveying.

**Features:**
- Property boundary calculations
- Multi-unit conversions (meters, feet, acres)
- Detailed survey reports
- Real estate applications

**Conversions Included:**
- Square meters to square feet
- Square meters to acres
- Meters to feet
- Boundary segment measurements

**Sample Output:**
```
╔═══════════════════════════════════════════════════════╗
║           PROPERTY SURVEY REPORT                      ║
╚═══════════════════════════════════════════════════════╝

Property Owner: John Smith
Address: 123 Main Street, Springfield

--- AREA MEASUREMENTS ---
  1200.00 m²
  12916.71 ft²
  0.30 acres

--- PERIMETER MEASUREMENTS ---
  140.00 m
  459.32 ft
```

**What You'll Learn:**
- Real-world application design
- Unit conversion techniques
- Report generation
- Professional output formatting

---

### 06. Interactive Calculator (`06_interactive_calculator.cpp`)

**Difficulty:** 🟡 Intermediate  
**Topics:** User input, Interactive CLI, Menu systems

Build an interactive command-line polygon calculator.

**Features:**
- Menu-driven interface
- Dynamic polygon creation from user input
- Multiple calculation modes
- Input validation and error recovery

**Available Calculators:**
1. Custom Polygon - User defines vertices
2. Regular Polygon - Specify sides and length
3. Rectangle - Width and height
4. Circle - Radius

**Sample Interaction:**
```
╔════════════════════════════════════════╗
║  Polygon Geometry Calculator           ║
╠════════════════════════════════════════╣
║  1. Custom Polygon                     ║
║  2. Regular Polygon                    ║
║  3. Rectangle                          ║
║  4. Circle                             ║
║  5. Exit                               ║
╚════════════════════════════════════════╝
Choose an option: 1

=== Custom Polygon Calculator ===
Enter the number of vertices (minimum 3): 4
Enter coordinates for each vertex (x y):
Vertex 1: 0 0
Vertex 2: 5 0
Vertex 3: 5 5
Vertex 4: 0 5

--- Results ---
Area: 25.0000 square units
Perimeter: 20.0000 units
```

**What You'll Learn:**
- Building interactive applications
- User input handling
- Menu systems
- Error recovery strategies

---

### 07. Performance Comparison (`07_performance_comparison.cpp`)

**Difficulty:** 🔴 Advanced  
**Topics:** Benchmarking, Optimization, Performance analysis

Comprehensive performance analysis and optimization techniques.

**Benchmarks:**
- Small polygons (3 vertices)
- Medium polygons (20 vertices)
- Large polygons (100 vertices)
- Very large polygons (1000 vertices)
- Float vs double performance

**Performance Metrics:**
- Time per calculation (nanoseconds)
- Throughput (calculations/second)
- Memory usage patterns
- Cache efficiency

**Sample Output:**
```
╔═══════════════════════════════════════════════════════╗
║  Small Polygons (Triangle - 3 vertices)              ║
╚═══════════════════════════════════════════════════════╝

--- float with 3 vertices ---
  Total time: 2.15 ms
  Average time: 21.50 ns per calculation
  Throughput: 46511627.91 calculations/second

--- double with 3 vertices ---
  Total time: 2.87 ms
  Average time: 28.70 ns per calculation
  Throughput: 34843205.57 calculations/second
```

**What You'll Learn:**
- Performance measurement techniques
- Optimization strategies
- Float vs double tradeoffs
- Scaling behavior (O(n) complexity)

---

### 08. Batch Processing (`08_batch_processing.cpp`)

**Difficulty:** 🔴 Advanced  
**Topics:** Bulk operations, Statistics, Data pipelines

Process multiple polygons efficiently with statistical analysis.

**Features:**
- Batch polygon generation
- Parallel processing patterns
- Statistical analysis (mean, std dev, min, max)
- Top-N queries
- Data aggregation

**Statistics Computed:**
- Total area/perimeter
- Mean and standard deviation
- Min/max values
- Success/failure rates

**Sample Output:**
```
╔═══════════════════════════════════════════════════════╗
║              STATISTICAL ANALYSIS                     ║
╚═══════════════════════════════════════════════════════╝

--- AREA STATISTICS ---
  Count: 100
  Total: 523847.23 square units
  Mean: 5238.47 square units
  Std Dev: 2451.32 square units
  Min: 314.16 square units
  Max: 15241.89 square units

--- TOP 10 LARGEST POLYGONS (by area) ---
  1. POLY_42 - Area: 15241.89, Perimeter: 542.31, Vertices: 8
  2. POLY_17 - Area: 14523.12, Perimeter: 498.76, Vertices: 6
```

**What You'll Learn:**
- Batch processing patterns
- Statistical analysis
- Data aggregation techniques
- Performance with large datasets

---

### 09. Compile-Time Examples (`09_compile_time_examples.cpp`)

**Difficulty:** 🔴 Advanced  
**Topics:** constexpr, Template metaprogramming, Zero-cost abstractions

Leverage C++26's compile-time evaluation for zero runtime overhead.

**Demonstrates:**
- `constexpr` polygon calculations
- `consteval` functions
- `static_assert` validation
- Compile-time constants
- Zero runtime cost

**Compile-Time Calculations:**
- Triangle areas
- Square areas
- Perimeters
- Coordinate operations
- Point distances

**Sample Output:**
```
=== Compile-Time Examples ===

--- Compile-Time Calculations ---
These values are calculated at compile time (zero runtime cost):

Triangle area (compile-time): 6.0000
Square area (compile-time): 25.0000
Square perimeter (compile-time): 20.0000

--- Benefits of Compile-Time Calculations ---
✓ Zero runtime overhead
✓ Errors caught at compile time
✓ Results embedded in binary
✓ Can be used in other constexpr contexts
✓ Perfect for lookup tables and constants
```

**What You'll Learn:**
- Compile-time programming
- `constexpr` and `consteval` usage
- Template metaprogramming
- Zero-cost abstractions
- Performance optimization

---

### 10. Visualization Data (`10_visualization_data.cpp`)

**Difficulty:** 🟡 Intermediate  
**Topics:** Data export, Visualization, File formats

Export polygon data to various formats for visualization tools.

**Export Formats:**
- **JSON** - Web applications, APIs
- **CSV** - Excel, data analysis
- **SVG** - Vector graphics, web browsers

**Features:**
- Multiple export formats
- Bounding box calculation
- Coordinate transformation
- Ready for plotting tools

**Generated Files:**
- `pentagon.json` - JSON format
- `pentagon.csv` - CSV format
- `pentagon.svg` - Scalable vector graphics
- `star.json`, `star.csv`, `star.svg` - Additional examples

**JSON Format:**
```json
{
  "polygon": {
    "vertices": [
      {"x": 50.0, "y": 10.0},
      {"x": 90.0, "y": 40.0},
      {"x": 70.0, "y": 80.0}
    ],
    "properties": {
      "vertex_count": 3,
      "area": 1200.0,
      "perimeter": 196.85
    }
  }
}
```

**What You'll Learn:**
- Data export patterns
- Multiple file format support
- Integration with visualization tools
- SVG generation basics

---

## 🎓 Quick Start Guide

### For Complete Beginners

Start with these examples in order:

1. **01_basic_usage** - Learn the fundamentals
2. **02_polygon_class** - Understand the class interface
3. **04_error_handling** - Learn proper error handling
4. **06_interactive_calculator** - Build something interactive

### For Intermediate Users

Skip to these examples:

1. **03_different_types** - Understand type selection
2. **05_real_world_land_surveying** - See practical applications
3. **08_batch_processing** - Learn bulk operations
4. **10_visualization_data** - Export and visualize data

### For Advanced Users

Focus on optimization and advanced features:

1. **07_performance_comparison** - Optimize your code
2. **09_compile_time_examples** - Zero-cost abstractions
3. **08_batch_processing** - Large-scale processing

## 🔧 Advanced Topics

### Custom Compilation Flags

```bash
# Maximum optimization
cmake -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_FLAGS="-O3 -march=native -flto"

# Debug with sanitizers
cmake -B build \
    -DCMAKE_BUILD_TYPE=Debug \
    -DPOLYGON_GEOMETRY_ENABLE_SANITIZERS=ON
```

### Profiling Examples

```bash
# Linux perf
perf record ./build/examples/07_performance_comparison
perf report

# Valgrind callgrind
valgrind --tool=callgrind ./build/examples/08_batch_processing
kcachegrind callgrind.out.*
```

### Memory Analysis

```bash
# Check for leaks
valgrind --leak-check=full ./build/examples/06_interactive_calculator

# Memory usage profiling
valgrind --tool=massif ./build/examples/08_batch_processing
ms_print massif.out.*
```

## 📝 Example Template

To create your own example:

```cpp
/**
 * @file my_example.cpp
 * @brief Brief description
 * @author Your Name
 * @date 2026
 */

#include "polygon_geometry.hpp"
#include <iostream>

using namespace geometry;

int main() {
    std::cout << "=== My Custom Example ===\n";
    
    // Your code here
    std::vector<Point2D<double>> triangle = {
        {0.0, 0.0},
        {1.0, 0.0},
        {0.5, 1.0}
    };
    
    auto area = calculate_area_shoelace(triangle);
    if (area) {
        std::cout << "Area: " << area->value << "\n";
    }
    
    return 0;
}
```

Add to `CMakeLists.txt`:
```cmake
list(APPEND EXAMPLES my_example)
```

## 🎯 Learning Path

### Beginner Track (2-4 hours)
1. Read main README.md
2. Build and run `01_basic_usage`
3. Study and run `02_polygon_class`
4. Experiment with `04_error_handling`
5. Try `06_interactive_calculator`

### Intermediate Track (4-6 hours)
1. Complete Beginner Track
2. Study `03_different_types`
3. Implement `05_real_world_land_surveying` modifications
4. Explore `10_visualization_data`
5. Create your own example

### Advanced Track (6-10 hours)
1. Complete Intermediate Track
2. Analyze `07_performance_comparison`
3. Master `09_compile_time_examples`
4. Optimize `08_batch_processing`
5. Contribute to the library

## 📚 Additional Resources

### Documentation
- [Main README](../README.md) - Library overview
- [API Reference](../docs/API.md) - Detailed API documentation
- [Test Suite](../tests/README.md) - Testing examples

### External Resources
- [Shoelace Theorem](https://en.wikipedia.org/wiki/Shoelace_formula) - Mathematical background
- [C++26 Features](https://en.cppreference.com/w/cpp/26) - Language features used

## 🤝 Contributing Examples

Have a great example to share? Contributions are welcome!

1. Write your example following the template
2. Add comprehensive comments
3. Update this README
4. Submit a pull request

### Example Contribution Guidelines
- Clear, concise code
- Comprehensive comments
- Demonstrates specific features
- Includes sample output
- Follows existing style

## 💡 Tips and Tricks

### Performance Tips
- Use `float` for graphics/games (better cache usage)
- Use `double` for general calculations (standard precision)
- Use `long double` for scientific computing (high precision)
- Reserve vector capacity when known: `vertices.reserve(n)`

### Debugging Tips
- Enable sanitizers for development builds
- Use verbose error messages
- Check `std::optional` before dereferencing
- Validate polygon vertices (minimum 3 points)

### Best Practices
- Always check return values (`std::optional`)
- Use strong types to prevent errors
- Validate input before calculations
- Document your polygon coordinate system
- Consider numerical stability for very large/small values

## 📞 Support

Need help with the examples?

1. Check this README first
2. Review the example source code comments
3. See the main [README.md](../README.md)
4. Open an issue on GitHub
5. Join discussions

## 🎉 What's Next?

After working through the examples:

1. **Read the API documentation** for complete reference
2. **Run the test suite** to see comprehensive coverage
3. **Integrate the library** into your own projects
4. **Contribute examples** to help others learn
5. **Share your use cases** with the community

---

**Happy Coding! 🚀**
