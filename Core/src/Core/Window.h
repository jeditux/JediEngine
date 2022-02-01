//
// Created by jeditux on 20.10.2021.
//

#pragma once

#include "Core/Event.h"

#include <string>
#include <functional>
#include <memory>
#include <Rendering/ShaderProgram.h>
#include <Core/ResourceManager.h>

struct GLFWwindow;

namespace Core {
    class Window {
    public:
        using EventCallbackFn = std::function<void(BaseEvent&)>;

        Window(std::string title, const unsigned int width, const unsigned int height, std::string executablePath);
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

        std::shared_ptr<Rendering::ShaderProgram> m_pShaderProgram;
        std::shared_ptr<Rendering::ShaderProgram> m_pTextureShader;
        std::shared_ptr<Rendering::Texture2D> m_pWallTexture;
        unsigned int m_vao;
        std::unique_ptr<Core::ResourceManager> m_pResourceManager;
        std::string m_executablePath;
    };
}
