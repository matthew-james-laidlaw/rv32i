include(GoogleTest)

if(BUILD_ACCEPTANCE_TESTS)
    add_subdirectory(acceptance)
endif()

add_subdirectory(unit)
