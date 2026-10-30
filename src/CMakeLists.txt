set(EMU_LIB_TARGET emucore)

add_library(${EMU_LIB_TARGET}
    core.cpp
    instruction.cpp
    memory.cpp
    registers.cpp
)

target_include_directories(${EMU_LIB_TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${EMU_LIB_TARGET}
    PUBLIC
        cxx_std_23
)
