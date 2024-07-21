cmake_minimum_required(VERSION 3.5.0)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_executable(lin_alg_test lin_alg.cpp)
add_executable(transformation_test transformation_test.cpp)

target_link_libraries(
    lin_alg_test
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    lin_alg
)

target_link_libraries(
    transformation_test
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    lin_alg
)
