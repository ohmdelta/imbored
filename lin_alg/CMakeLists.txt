cmake_minimum_required(VERSION 3.5.0)
project(lin_alg VERSION 0.1.0 LANGUAGES C CXX)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

add_library(
    lin_alg
    SHARED
    src/coordinate.cpp
    src/transformation.cpp
)

target_include_directories(
    lin_alg
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    include
)
set_target_properties(lin_alg PROPERTIES VERSION 1.0.0 SOVERSION 1)
