//
// Created by jeditux on 19.10.2021.
//

#include "Core/Application.h"
#include "Core/Log.h"
#include "Window.h"

namespace Core {

    Application::Application(const std::string& executablePath)
        : m_executablePath(executablePath) {
        LOG_INFO("Starting Application");
    }

    Application::~Application() {
        LOG_INFO("Closing Application");
    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char *title) {
        m_pWindow = std::make_unique<Window>(title, window_width, window_height, m_executablePath);
//        m_pWindow->setExecutablePath(m_executablePath);
        m_dispatcher.addEventHandler<ResizeEvent>([](ResizeEvent& event) {
            LOG_INFO("[EVENT] Changed size to {0}x{1}", event.width, event.height);
        });
        m_dispatcher.addEventHandler<MouseMoveEvent>([](MouseMoveEvent& event) {
            LOG_INFO("[EVENT] Mouse moved to {0}x{1}", event.x, event.y);
        });
        m_pWindow->setEventCallback([&](BaseEvent& event) {
            m_dispatcher.dispatch(event);
        });

        while (!m_pWindow->getWindowClose())
        {
            m_pWindow->on_update();
            on_update();
        }
        return 0;
    }
}
