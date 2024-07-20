cmake_minimum_required(VERSION 3.5.0)
project(gcode_renderer VERSION 0.1.0 LANGUAGES C CXX)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(lin_alg)
# find_library(lin_alg lin_alg)
# target_link_libraries(main lin_alg)

add_executable(Main main.cpp)
target_link_libraries(Main lin_alg )
