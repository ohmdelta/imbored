cmake_minimum_required(VERSION 3.5.0)

set(PROJECT_NAME_STR polynomial)
set(PROJECT_UNIT_TESTS_NAME ${PROJECT_NAME_STR}_unit_tests)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

function(add_boost_test SOURCE_FILE_NAME DEPENDENCY_LIB)
    get_filename_component(TEST_EXECUTABLE_NAME ${SOURCE_FILE_NAME} NAME_WE)

    add_executable(${TEST_EXECUTABLE_NAME} ${SOURCE_FILE_NAME})
    target_link_libraries(${TEST_EXECUTABLE_NAME} 
                          ${DEPENDENCY_LIB}
                          ${Boost_FILESYSTEM_LIBRARY}
                          ${Boost_SYSTEM_LIBRARY}
                          ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )

    file(READ "${SOURCE_FILE_NAME}" SOURCE_FILE_CONTENTS)
    
    string(REGEX MATCHALL "BOOST_AUTO_TEST_CASE\\( *([A-Za-z_0-9]+) *\\)" 
           FOUND_TESTS ${SOURCE_FILE_CONTENTS})

    # message(PROJECT_SOURCE_DIR="${FOUND_TESTS}")
    foreach(HIT ${FOUND_TESTS})
        string(REGEX REPLACE ".*\\( *([A-Za-z_0-9]+) *\\).*" "\\1" TEST_NAME ${HIT})
        
        add_test(NAME "${TEST_EXECUTABLE_NAME}.${TEST_NAME}" 
                 COMMAND ${TEST_EXECUTABLE_NAME}
                 --run_test=*/${TEST_NAME} --catch_system_error=yes)
    endforeach()
endfunction()

enable_testing()

enable_testing()
add_boost_test(quadratic.cpp polynomial)
add_boost_test(cubic.cpp polynomial)
add_boost_test(quartic.cpp polynomial)
