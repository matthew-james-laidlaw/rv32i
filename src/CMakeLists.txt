set(EMULATOR_LIB_NAME emucore)

add_library(${EMULATOR_LIB_NAME}
    core.cpp
    instruction.cpp
    memory.cpp
    registers.cpp
)

target_include_directories(${EMULATOR_LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${EMULATOR_LIB_NAME}
    PUBLIC
        cxx_std_23
)
