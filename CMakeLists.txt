cmake_minimum_required(VERSION 3.28.3)

project(EMU LANGUAGES CXX)

enable_testing()

# CMake Modules
# -------------

include(cmake/cpm_fetch_dependencies.cmake)

# Build Options
# -------------

option(BUILD_ACCEPTANCE_TESTS "Fetch, build, and run the riscv-tests rv32ui acceptance test suite" OFF)
if(BUILD_ACCEPTANCE_TESTS)
    include(${PROJECT_SOURCE_DIR}/cmake/riscv_tests.cmake)
endif()

# Subdirectories
# -------------

add_subdirectory(src)
add_subdirectory(tests)
