cmake_minimum_required(VERSION 3.5.0)
project(polynomial VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(
  polynomial
  SHARED
  ${SOURCES}
)

target_include_directories(
  polynomial
  PUBLIC
  # ${CMAKE_CURRENT_SOURCE_DIR}
  include
)

set_target_properties(polynomial PROPERTIES VERSION 1.0.0 SOVERSION 1)

enable_testing()
add_subdirectory(test)
