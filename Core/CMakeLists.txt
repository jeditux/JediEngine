cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME Core)

set(ENGINE_PUBLIC_INCLUDES
        include/Core/Application.h
        include/Core/Log.h)

set(ENGINE_PRIVATE_SOURCES
        src/Core/Application.cpp)

add_library(${ENGINE_PROJECT_NAME} STATIC ${ENGINE_PUBLIC_INCLUDES} ${ENGINE_PRIVATE_SOURCES})

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)
