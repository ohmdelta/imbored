cmake_minimum_required(VERSION 3.22.0)
project(gcode_renderer VERSION 0.1.0 LANGUAGES C CXX)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package( OpenCV REQUIRED )
find_package(Curses REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(lin_alg)
add_subdirectory(tensor)
add_subdirectory(polynomial)
add_subdirectory(renderer)
add_subdirectory(test)

add_executable(Main main.cpp)
target_link_libraries(Main lin_alg)
target_link_libraries(Main renderer)
target_link_libraries(Main ${OpenCV_LIBS})


add_executable(render_balls render_balls.cpp)
target_link_libraries(render_balls lin_alg)
target_link_libraries(render_balls renderer)

add_executable(render_donut render_donut.cpp)
target_link_libraries(render_donut lin_alg)
target_link_libraries(render_donut renderer)
target_link_libraries(render_donut ncurses)

enable_testing()

