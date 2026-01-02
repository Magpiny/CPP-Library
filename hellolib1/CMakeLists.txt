# minimum version of CMAKE reuired to run this project
cmake_minimum_required(VERSION 4.2)

# set the project name and version
project(hellolib LANGUAGES CXX)

# export json compile_commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set c++ version, make it mandatory and set cmake 
# extensions to OFF for platform agnostic usage

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS 0FF)

# set executable name
add_executable(myhellolib)
target_sources(myhellolib PRIVATE myhello.cpp)

### Add library to be used with the executable
add_library(coformat
    libs/coformat/coformat.h
    libs/coformat/coformat.c++)

# tell the compiler where to get the library headers included
# in the source code
target_include_directories(myhellolib PUBLIC libs/coformat/)

# link the library with program(connect the libray to the app)
target_link_libraries(myhellolib PUBLIC coformat)

