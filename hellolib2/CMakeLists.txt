cmake_minimum_required(VERSION 4.2)

project(helloformatwithlib LANGUAGES CXX)

if(MSVC)
    message(STATUS "Using MSVC STL on Windows")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    message(STATUS "Using libc++ on macOS")
elseif(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    message(STATUS "Using libc++ on FreeBSD")
elseif(ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    message(STATUS "Using libc++ on Android")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
    message(STATUS "Using libstdc++ with Clang on Linux")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Using libstdc++ with GCC")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

### ADD LIBRARIES
add_library(coformat 
    coformat.h
    coformat.c++)

add_executable(myhello myhello.cpp)
target_link_libraries(myhello PUBLIC coformat)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
