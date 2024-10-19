cmake_minimum_required(VERSION 3.5)

project(s21_matrix VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# -------- GOOGLE TEST -----------------------------------------------
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)
if (CMAKE_VERSION VERSION_LESS 3.0.0)
    include_directories("${gtest_SOURCE_DIR}/include")
endif ()
# -------------------------------------------------------------------------


include_directories("${gtest_SOURCE_DIR}/include")

add_library(s21_matrix_oop STATIC
    s21_matrix_oop.h
    s21_matrix_oop.cc
    )

add_executable(s21_matrix matrix_main.cc )
target_link_libraries(s21_matrix s21_matrix_oop)

add_executable(matrix_test matrix_test.cc)
target_link_libraries(matrix_test gtest_main gmock pthread s21_matrix_oop)

