//
// Created by jeditux on 20.10.2021.
//

#include "Window.h"
#include "Core/Log.h"
#include "Rendering/Texture2D.h"

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
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
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
            MouseMoveEvent event(static_cast<unsigned int>(xpos), static_cast<unsigned int>(ypos));
            data.eventCallbackFn(event);
        });

        glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow* pWindow, int button, int action, int mods) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
            double xPos, yPos;
            glfwGetCursorPos(pWindow, &xPos, &yPos);
            MouseButton mouseButton;
            switch (button) {
                case GLFW_MOUSE_BUTTON_LEFT:
                    mouseButton = MouseButton::left;
                    break;
                case GLFW_MOUSE_BUTTON_RIGHT:
                    mouseButton = MouseButton::right;
                    break;
            }
            if (action == GLFW_PRESS) {
                MouseButtonPressEvent event(static_cast<unsigned int>(xPos), static_cast<unsigned int>(yPos), mouseButton);
                data.eventCallbackFn(event);
            } else if (action == GLFW_RELEASE) {
                MouseButtonReleaseEvent event(static_cast<unsigned int>(xPos), static_cast<unsigned int>(yPos), mouseButton);
                data.eventCallbackFn(event);
            }
        });

        m_pResourceManager = std::make_unique<Core::ResourceManager>(m_executablePath);
        m_pShaderProgram = m_pResourceManager->loadShader("triangle", "triangle.vert", "triangle.frag");
        m_pWallTexture = m_pResourceManager->loadTexture("wall", "container.jpg");

        unsigned int VBO, EBO;
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);

        m_pTextureShader = m_pResourceManager->loadShader("texture", "texture.vert", "texture.frag");
        m_pTextureShader->use();
        glActiveTexture(GL_TEXTURE0);
        m_pWallTexture->bind();
        m_pTextureShader->setInt("ourTexture", 0);

        return 0;
    }

    void Window::shutdown() {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    void Window::on_update() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        m_pWallTexture->bind();
        m_pTextureShader->use();
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

//        ImGuiIO& io = ImGui::GetIO();
//        io.DisplaySize.x = static_cast<float>(getWidth());
//        io.DisplaySize.y = static_cast<float>(getHeight());
//
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//        ImGui::NewFrame();
//
//        ImGui::ShowDemoWindow();
//
//        ImGui::Render();
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }

    bool Window::getWindowClose() {
        return glfwWindowShouldClose(m_pWindow);
    }
}
