//
// Created by jeditux on 20.10.2021.
//

#pragma once

#include "Core/Event.h"

#include <string>
#include <functional>

struct GLFWwindow;

namespace Core {
    class Window {
    public:
        using EventCallbackFn = std::function<void(BaseEvent&)>;

        Window(std::string title, const unsigned int width, const unsigned int height);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        void on_update();
        unsigned int getWidth() const { return m_data.width; }
        unsigned int getHeight() const { return m_data.height; }

        void setEventCallback(const EventCallbackFn& callback) {
            m_data.eventCallbackFn = callback;
        }

        bool getWindowClose();

    private:
        struct WindowData {
            std::string title;
            unsigned int width;
            unsigned int height;
            EventCallbackFn eventCallbackFn;
        };

        int init();
        void shutdown();

        GLFWwindow* m_pWindow = nullptr;
        WindowData m_data;

        unsigned int m_shaderProgram;
        unsigned int m_vao;
    };
}