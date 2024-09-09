cmake_minimum_required(VERSION 3.22.0)
set(CMAKE_CXX_STANDARD 20)
project(tensor VERSION 0.1.0 LANGUAGES C CXX)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)
message("Hello: " ${CMAKE_CXX_STANDARD})
add_library(
  tensor    
  src/matrix.cpp
)

target_include_directories(
    tensor
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    include
)
set_target_properties(tensor PROPERTIES VERSION 1.0.0 SOVERSION 1)

enable_testing()
add_subdirectory(test)
