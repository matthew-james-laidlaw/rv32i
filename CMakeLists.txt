cmake_minimum_required(VERSION 3.28.3)
project(RV32I LANGUAGES CXX)

add_executable(RV32I
    src/main.cpp
)

target_compile_features(RV32I PRIVATE cxx_std_23)
