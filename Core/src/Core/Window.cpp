//
// Created by jeditux on 20.10.2021.
//

#include "Window.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

namespace Core {

    static bool s_GLFW_initialized = false;

    Window::Window(std::string title, const unsigned int width, const unsigned int height, std::string executablePath)
    : m_data({std::move(title), width, height})
    , m_executablePath(std::move(executablePath)) {
        int resultCode = init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
        ImGui_ImplOpenGL3_Init();
    }

    Window::~Window() {
        shutdown();
    }

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    int Window::init() {
        LOG_INFO("Creating window '{0}' with size {1}x{2}", m_data.title, m_data.width, m_data.height);

        if (!s_GLFW_initialized) {
            if (!glfwInit()) {
                LOG_CRITICAL("Can't initialize GLFW!");
                return -1;
            }
            s_GLFW_initialized = true;
        }

        m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
        if (!m_pWindow) {
            LOG_CRITICAL("Can't create window {0}", m_data.title);
            glfwTerminate();
            return -2;
        }

        glfwMakeContextCurrent(m_pWindow);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            LOG_CRITICAL("Failed to initialize GLAD");
            return -3;
        }

        glfwSetWindowUserPointer(m_pWindow, &m_data);
        glfwSetWindowSizeCallback(m_pWindow, [](GLFWwindow* pWindow, int width, int height) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
            data.width = width;
            data.height = height;
            ResizeEvent event(width, height);
            data.eventCallbackFn(event);

            glViewport(0, 0, width, height);
        });

        glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow* pWindow, double xpos, double ypos) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
            MouseMoveEvent event(xpos, ypos);
            data.eventCallbackFn(event);
        });

        m_pResourceManager = std::make_unique<Core::ResourceManager>(m_executablePath);
        m_pShaderProgram = m_pResourceManager->loadShader("triangle", "triangle.vert", "triangle.frag");

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &m_vao);
        glBindVertexArray(m_vao);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);

        return 0;
    }

    void Window::shutdown() {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    void Window::on_update() {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        m_pShaderProgram->use();
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(getWidth());
        io.DisplaySize.y = static_cast<float>(getHeight());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }

    bool Window::getWindowClose() {
        return glfwWindowShouldClose(m_pWindow);
    }
}
