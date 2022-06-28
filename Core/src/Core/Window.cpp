//
// Created by jeditux on 20.10.2021.
//

#include "Window.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core {

    static bool s_GLFW_initialized = false;

    const std::unordered_map<size_t, Key> Window::KEY_MAPPINGS = {{GLFW_KEY_UP, Key::UP},
                                                                  {GLFW_KEY_DOWN, Key::DOWN},
                                                                  {GLFW_KEY_LEFT, Key::LEFT},
                                                                  {GLFW_KEY_RIGHT, Key::RIGHT}
    };

    Window::Window(std::string title, const unsigned int width, const unsigned int height, std::string executablePath)
    : m_data({std::move(title), width, height})
    , m_executablePath(std::move(executablePath)) {
        int resultCode = init();
    }

    Window::~Window() {
        shutdown();
    }

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

        glfwSetKeyCallback(m_pWindow, [](GLFWwindow* pWindow, int key, int scancode, int action, int mods) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
            if (action == GLFW_PRESS) {
                KeyPressEvent event(KEY_MAPPINGS.count(key) > 0 ? KEY_MAPPINGS.at(key) : Key::UNSUPPORTED);
                data.eventCallbackFn(event);
            } else if (action == GLFW_RELEASE) {
                KeyReleaseEvent event(KEY_MAPPINGS.count(key) > 0 ? KEY_MAPPINGS.at(key)  : Key::UNSUPPORTED);
                data.eventCallbackFn(event);
            }
        });

        return 0;
    }

    void Window::shutdown() {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    void Window::setEventCallback(const EventCallbackFn& callback) {
        m_data.eventCallbackFn = callback;
    }

    void Window::setRenderFunction(const RenderFn& renderFunction) {
        m_renderFunction = renderFunction;
    }

    void Window::render() {

        m_renderFunction();

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }

    bool Window::getWindowClose() {
        return glfwWindowShouldClose(m_pWindow);
    }
}
