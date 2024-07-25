cmake_minimum_required(VERSION 3.5.0)
project(gcode_renderer VERSION 0.1.0 LANGUAGES C CXX)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(
    renderer
    SHARED
    renderer.hpp
    world.hpp
    shapes.hpp
    shapes.cpp
    display.hpp
    display.cpp
)

target_include_directories(
    renderer
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(renderer lin_alg)
