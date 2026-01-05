# CMakeLists.txt for AreaPeriPoly Test Suite
cmake_minimum_required(VERSION 4.2 FATAL_ERROR)

message(STATUS "Configuring AreaPeriPoly Test Suite")

# Fetch Google Test
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
    FIND_PACKAGE_ARGS NAMES GTest
)

# Fetch Google Benchmark
FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG        v1.9.1
    FIND_PACKAGE_ARGS NAMES benchmark
)

# Configure Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# Configure Google Benchmark
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)

# Make dependencies available
FetchContent_MakeAvailable(googletest benchmark)

# Enable testing
enable_testing()
include(GoogleTest)

# Compiler options for tests
add_library(test_compiler_options INTERFACE)
target_compile_features(test_compiler_options INTERFACE cxx_std_26)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(test_compiler_options INTERFACE
        -Wall -Wextra -Wpedantic
        $<$<CONFIG:Debug>:-g -O0>
        $<$<CONFIG:Release>:-O3 -DNDEBUG>
    )
elseif(MSVC)
    target_compile_options(test_compiler_options INTERFACE
        /W4 /permissive-
        $<$<CONFIG:Debug>:/Od /Zi>
        $<$<CONFIG:Release>:/O2 /DNDEBUG>
    )
endif()

# ============================================================================
# Unit Tests
# ============================================================================

set(UNIT_TEST_SOURCES
    test_basic_types.cpp
    test_shoelace.cpp
    test_perimeter.cpp
    test_regular_polygons.cpp
    test_standard_shapes.cpp
    test_polygon_class.cpp
    test_edge_cases.cpp
    test_constexpr.cpp
)

# Create unit test executable
add_executable(areaperipoly_tests ${UNIT_TEST_SOURCES})

target_link_libraries(areaperipoly_tests
    PRIVATE
        AreaPeriPoly::AreaPeriPoly
        GTest::gtest
        GTest::gtest_main
        test_compiler_options
)

# Discover and register tests
gtest_discover_tests(areaperipoly_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTIES
        LABELS "unit"
    DISCOVERY_TIMEOUT 30
)

# Add a custom target to run only unit tests
add_custom_target(run_unit_tests
    COMMAND ${CMAKE_CTEST_COMMAND} -L unit --output-on-failure
    DEPENDS areaperipoly_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running unit tests"
    VERBATIM
)

# ============================================================================
# Integration Tests (if needed in the future)
# ============================================================================

# Placeholder for integration tests
# add_executable(areaperipoly_integration_tests integration_test.cpp)
# target_link_libraries(areaperipoly_integration_tests ...)

# ============================================================================
# Performance Benchmarks
# ============================================================================

add_executable(areaperipoly_benchmarks benchmark_performance.cpp)

target_link_libraries(areaperipoly_benchmarks
    PRIVATE
        AreaPeriPoly::AreaPeriPoly
        benchmark::benchmark
        benchmark::benchmark_main
        test_compiler_options
)

# Don't run benchmarks as part of regular test suite
# They can be run manually with: ./areaperipoly_benchmarks
add_custom_target(run_benchmarks
    COMMAND $<TARGET_FILE:areaperipoly_benchmarks>
        --benchmark_out=benchmark_results.json
        --benchmark_out_format=json
        --benchmark_repetitions=3
        --benchmark_report_aggregates_only=true
    DEPENDS areaperipoly_benchmarks
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running performance benchmarks"
    VERBATIM
)

# ============================================================================
# Memory and Sanitizer Tests
# ============================================================================

if(areaperipoly_ENABLE_SANITIZERS)
    # Create sanitizer-enabled test executable
    add_executable(areaperipoly_tests_sanitized ${UNIT_TEST_SOURCES})
    
    target_link_libraries(areaperipoly_tests_sanitized
        PRIVATE
            AreaPeriPoly::AreaPeriPoly
            GTest::gtest
            GTest::gtest_main
            test_compiler_options
    )
    
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(areaperipoly_tests_sanitized PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
            -fno-optimize-sibling-calls
        )
        target_link_options(areaperipoly_tests_sanitized PRIVATE
            -fsanitize=address,undefined
        )
    endif()
    
    # Register sanitized tests
    gtest_discover_tests(areaperipoly_tests_sanitized
        PROPERTIES
            LABELS "sanitizer"
    )
    
    add_custom_target(run_sanitizer_tests
        COMMAND ${CMAKE_CTEST_COMMAND} -L sanitizer --output-on-failure
        DEPENDS areaperipoly_tests_sanitized
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running tests with sanitizers"
        VERBATIM
    )
endif()

# ============================================================================
# Test Coverage (GCC/Clang only)
# ============================================================================

option(ENABLE_COVERAGE "Enable code coverage" OFF)

if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Code coverage enabled")
    
    add_executable(areaperipoly_tests_coverage ${UNIT_TEST_SOURCES})
    
    target_link_libraries(areaperipoly_tests_coverage
        PRIVATE
            AreaPeriPoly::AreaPeriPoly
            GTest::gtest
            GTest::gtest_main
            test_compiler_options
    )
    
    target_compile_options(areaperipoly_tests_coverage PRIVATE
        --coverage
        -fprofile-arcs
        -ftest-coverage
    )
    
    target_link_options(areaperipoly_tests_coverage PRIVATE
        --coverage
    )
    
    # Add coverage target
    add_custom_target(coverage
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        COMMAND lcov --capture --directory . --output-file coverage.info
        COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info
        COMMAND lcov --remove coverage.info '*/tests/*' --output-file coverage.info
        COMMAND lcov --remove coverage.info '*/build/*' --output-file coverage.info
        COMMAND lcov --list coverage.info
        COMMAND genhtml coverage.info --output-directory coverage_html
        DEPENDS areaperipoly_tests_coverage
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating code coverage report"
        VERBATIM
    )
endif()

# ============================================================================
# Test Summary and Utilities
# ============================================================================

# Add a target to run all tests with verbose output
add_custom_target(test_verbose
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose --output-on-failure
    DEPENDS areaperipoly_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running all tests with verbose output"
    VERBATIM
)

# Add a target to run quick smoke tests
add_custom_target(smoke_tests
    COMMAND ${CMAKE_CTEST_COMMAND} -R "BasicTypes|Shoelace" --output-on-failure
    DEPENDS areaperipoly_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running smoke tests"
    VERBATIM
)

# Add memcheck target (valgrind)
find_program(VALGRIND_EXECUTABLE valgrind)
if(VALGRIND_EXECUTABLE)
    add_custom_target(memcheck
        COMMAND ${CMAKE_CTEST_COMMAND} 
            --force-new-ctest-process
            --test-action memcheck
            --output-on-failure
        DEPENDS areaperipoly_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running memory checks with Valgrind"
        VERBATIM
    )
    
    message(STATUS "Valgrind found: ${VALGRIND_EXECUTABLE}")
    message(STATUS "  Run 'make memcheck' to check for memory leaks")
endif()

# ============================================================================
# Test Configuration Summary
# ============================================================================

message(STATUS "")
message(STATUS "╔════════════════════════════════════════════════════════╗")
message(STATUS "║           Test Suite Configuration                     ║")
message(STATUS "╠════════════════════════════════════════════════════════╣")
message(STATUS "║ Unit Tests        : Enabled")
message(STATUS "║ Benchmarks        : Enabled")
message(STATUS "║ Sanitizers        : ${areaperipoly_ENABLE_SANITIZERS}")
message(STATUS "║ Coverage          : ${ENABLE_COVERAGE}")
if(VALGRIND_EXECUTABLE)
message(STATUS "║ Valgrind          : Found")
else()
message(STATUS "║ Valgrind          : Not Found")
endif()
message(STATUS "╠════════════════════════════════════════════════════════╣")
message(STATUS "║ Available targets:                                     ║")
message(STATUS "║   make test / ctest            - Run all tests         ║")
message(STATUS "║   make run_unit_tests          - Run unit tests only   ║")
message(STATUS "║   make run_benchmarks          - Run benchmarks        ║")
message(STATUS "║   make smoke_tests             - Quick smoke tests     ║")
message(STATUS "║   make test_verbose            - Verbose test output   ║")
if(areaperipoly_ENABLE_SANITIZERS)
message(STATUS "║   make run_sanitizer_tests     - Run with sanitizers   ║")
endif()
if(ENABLE_COVERAGE)
message(STATUS "║   make coverage                - Generate coverage     ║")
endif()
if(VALGRIND_EXECUTABLE)
message(STATUS "║   make memcheck                - Run Valgrind          ║")
endif()
message(STATUS "╚════════════════════════════════════════════════════════╝")
message(STATUS "")
