cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME Core)

set(ENGINE_PUBLIC_INCLUDES
        include/Core/Application.h
        include/Core/Log.h
        include/Core/Event.h
        include/Rendering/ShaderProgram.h
        include/Core/ResourceManager.h
        include/Rendering/Texture2D.h
        include/Rendering/GraphicsScene.h
        include/Rendering/GuiManager.h
        include/Rendering/Camera.h
        include/Rendering/GameObject.h
        include/Rendering/Sprite.h
)

set(ENGINE_PRIVATE_INCLUDES
        src/Core/Window.h
)

set(ENGINE_PRIVATE_SOURCES
        src/Core/Application.cpp
        src/Core/Window.cpp
        src/Rendering/ShaderProgram.cpp
        src/Core/ResourceManager.cpp
        src/Rendering/Texture2D.cpp
        src/Rendering/GraphicsScene.cpp
        src/Rendering/GuiManager.cpp
        src/Rendering/Camera.cpp
        src/Rendering/GameObject.cpp
        src/Rendering/Sprite.cpp
)

add_library(${ENGINE_PROJECT_NAME} STATIC ${ENGINE_PUBLIC_INCLUDES} ${ENGINE_PRIVATE_INCLUDES} ${ENGINE_PRIVATE_SOURCES})

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)

add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC glm)

set(IMGUI_INCLUDES
        ../external/imgui/imgui.h
        ../external/imgui/backends/imgui_impl_glfw.h
        ../external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES
        ../external/imgui/imgui.cpp
        ../external/imgui/backends/imgui_impl_glfw.cpp
        ../external/imgui/backends/imgui_impl_opengl3.cpp
        ../external/imgui/imgui_draw.cpp
        ../external/imgui/imgui_tables.cpp
        ../external/imgui/imgui_widgets.cpp
        ../external/imgui/imgui_demo.cpp
)

add_library(ImGui STATIC
        ${IMGUI_INCLUDES}
        ${IMGUI_SOURCES}
)

target_include_directories(ImGui PUBLIC ../external)
target_include_directories(ImGui PUBLIC ../external/imgui)
target_link_libraries(ImGui PRIVATE glad glfw)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE ImGui)
