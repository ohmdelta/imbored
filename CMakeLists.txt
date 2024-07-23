cmake_minimum_required(VERSION 3.5.0)
project(gcode_renderer VERSION 0.1.0 LANGUAGES C CXX)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(lin_alg)
add_subdirectory(renderer)
add_subdirectory(test)

add_executable(Main main.cpp)
target_link_libraries(Main lin_alg)
target_link_libraries(Main renderer)
target_link_libraries(Main ${OpenCV_LIBS} )

