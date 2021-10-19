cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME Core)

add_library(${ENGINE_PROJECT_NAME} STATIC
        src/Core/Utils/test.cpp
        include/Core/Utils/test.h)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)
