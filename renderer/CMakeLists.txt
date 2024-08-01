cmake_minimum_required(VERSION 3.5.0)
project(gcode_renderer VERSION 0.1.0 LANGUAGES C CXX)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

add_library(
  renderer
  SHARED
  src/display.cpp
  src/intersection.cpp
  src/plane.cpp
  src/sphere.cpp
  src/torus.cpp
  src/checkerboard.cpp
)


target_include_directories(
  renderer
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  include
)

set_target_properties(renderer PROPERTIES VERSION 1.0.0 SOVERSION 1)

target_link_libraries(renderer lin_alg polynomial)

enable_testing()
add_subdirectory(test)
