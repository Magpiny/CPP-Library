# CMakeLists.txt for AreaPeriPoly Examples
cmake_minimum_required(VERSION 4.2 FATAL_ERROR)

message(STATUS "Configuring AreaPeriPoly Examples")

# List of all example programs
set(EXAMPLES
    01_basic_usage
    02_polygon_class
    03_different_types
    04_error_handling
    05_real_world_land_surveying
    06_interactive_calculator
    07_performance_comparison
    08_batch_processing
    09_compile_time_examples
    10_visualization_data
)

# find_package(AreaPeriPoly REQUIRED)
# target_link_libraries(your_target PRIVATE AreaPeriPoly::AreaPeriPoly)

# Create a library for common example utilities (if needed)
add_library(example_utils INTERFACE)
target_compile_features(example_utils INTERFACE cxx_std_26)

# Configure compiler options for examples
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(example_utils INTERFACE
        -Wall -Wextra
        $<$<CONFIG:Debug>:-g -O0>
        $<$<CONFIG:Release>:-O3 -march=native>
    )
elseif(MSVC)
    target_compile_options(example_utils INTERFACE
        /W4 /permissive-
        $<$<CONFIG:Debug>:/Od /Zi>
        $<$<CONFIG:Release>:/O2>
    )
endif()

# Build each example
foreach(EXAMPLE ${EXAMPLES})
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    
    target_link_libraries(${EXAMPLE}
        INTERFACE
            AreaPeriPoly
            example_utils
    )
    
    # Set output directory
    set_target_properties(${EXAMPLE}
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples
    )
endforeach()

# Create a custom target to build all examples
add_custom_target(build_all_examples
    DEPENDS ${EXAMPLES}
    COMMENT "Building all examples"
)

# Create a custom target to run all examples sequentially
add_custom_target(run_all_examples
    COMMAND ${CMAKE_COMMAND} -E echo "=== Running All Examples ==="
    COMMENT "Running all example programs"
)

foreach(EXAMPLE ${EXAMPLES})
    add_custom_command(
        TARGET run_all_examples
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "--- Running ${EXAMPLE} ---"
        COMMAND $<TARGET_FILE:${EXAMPLE}>
        COMMAND ${CMAKE_COMMAND} -E echo ""
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/examples
        COMMENT "Running ${EXAMPLE}"
    )
endforeach()

# Individual run targets for each example
foreach(EXAMPLE ${EXAMPLES})
    add_custom_target(run_${EXAMPLE}
        COMMAND $<TARGET_FILE:${EXAMPLE}>
        DEPENDS ${EXAMPLE}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/examples
        COMMENT "Running ${EXAMPLE}"
        VERBATIM
    )
endforeach()

# Install examples (optional)
if(areaperipoly_INSTALL)
    install(
        TARGETS ${EXAMPLES}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/examples
        COMPONENT examples
    )
    
    # Install example source files for reference
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION ${CMAKE_INSTALL_DOCDIR}/examples
        FILES_MATCHING PATTERN "*.cpp"
        COMPONENT examples
    )
endif()

list(LENGTH EXAMPLES EXAMPLES_COUNT)

# Summary
message(STATUS "")
message(STATUS "╔════════════════════════════════════════════════════════╗")
message(STATUS "║           Examples Configuration                       ║")
message(STATUS "╠════════════════════════════════════════════════════════╣")
message(STATUS "║ Total Examples: ${EXAMPLES_COUNT}")
message(STATUS "║ Output Directory: ${CMAKE_BINARY_DIR}/examples")
message(STATUS "╠════════════════════════════════════════════════════════╣")
message(STATUS "║ Available targets:                                     ║")
message(STATUS "║   make build_all_examples    - Build all examples      ║")
message(STATUS "║   make run_all_examples      - Run all examples        ║")
message(STATUS "║   make run_<example_name>    - Run specific example    ║")
message(STATUS "╠════════════════════════════════════════════════════════╣")
message(STATUS "║ Example programs:                                      ║")

foreach(EXAMPLE ${EXAMPLES})
    message(STATUS "║   - ${EXAMPLE}")
endforeach()

message(STATUS "╚════════════════════════════════════════════════════════╝")
message(STATUS "")
