cmake_minimum_required(VERSION 3.5.0)

set(PROJECT_NAME_STR polynomial)
set(PROJECT_UNIT_TESTS_NAME ${PROJECT_NAME_STR}_unit_tests)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

file(
    GLOB_RECURSE ALL_TEST
    "*.cpp"
)

set(PROJECT_UNIT_TESTS_NAME ${PROJECT_NAME}_unit_tests)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_executable(${PROJECT_UNIT_TESTS_NAME}
  ${ALL_TEST}
)

add_definitions(-DBOOST_TEST_DYN_LINK)
target_link_libraries(
    ${PROJECT_UNIT_TESTS_NAME}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    polynomial
)


enable_testing()
add_test(PolynomialTest ${PROJECT_UNIT_TESTS_NAME})
