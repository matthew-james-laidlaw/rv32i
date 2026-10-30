set(ACCEPTANCE_TESTS_TARGET acceptance_tests)

add_executable(${ACCEPTANCE_TESTS_TARGET}
    acceptance_tests.cpp
)

target_include_directories(${ACCEPTANCE_TESTS_TARGET}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${ACCEPTANCE_TESTS_TARGET}
    emucore
    GTest::gtest_main
)

target_compile_definitions(${ACCEPTANCE_TESTS_TARGET}
    PRIVATE
        TEST_DATA_DIR="${RISCV_TESTS_BIN_DIR}"
)

add_dependencies(${ACCEPTANCE_TESTS_TARGET}
    riscv_test_bins
)

gtest_discover_tests(${ACCEPTANCE_TESTS_TARGET})
