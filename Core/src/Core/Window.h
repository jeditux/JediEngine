//
// Created by jeditux on 20.10.2021.
//

#pragma once

#include "Core/Event.h"

#include <string>
#include <functional>
#include <memory>

struct GLFWwindow;

namespace Core {
    class Window {
    public:
        using EventCallbackFn = std::function<void(BaseEvent&)>;
        using RenderFn = std::function<void()>;

        Window(std::string title, const unsigned int width, const unsigned int height, std::string executablePath);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        void render();
        unsigned int getWidth() const { return m_data.width; }
        unsigned int getHeight() const { return m_data.height; }
        GLFWwindow* getRawPtr() const { return m_pWindow; }

        void setEventCallback(const EventCallbackFn& callback);
        void setRenderFunction(const RenderFn& renderFunction);

        bool getWindowClose();
        void setExecutablePath(const std::string& path) { m_executablePath = path; }

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
        std::string m_executablePath;

        RenderFn m_renderFunction;
    };
}
