cmake_minimum_required(VERSION 3.22.0)
set(CMAKE_CXX_STANDARD 20)
project(tensor VERSION 0.1.0 LANGUAGES C CXX)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)
add_library(
  tensor    
  src/matrix.cpp
)
add_executable(
  profile_normal_test
  src/profile_normal_test.cpp
)
add_executable(
  profile_strassens_test
  src/profile_strassens_test.cpp
)
target_link_libraries(profile_normal_test tensor)
target_link_libraries(profile_strassens_test tensor)

target_include_directories(
    tensor
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    include
)
set_target_properties(tensor PROPERTIES VERSION 1.0.0 SOVERSION 1)

enable_testing()
add_subdirectory(test)
