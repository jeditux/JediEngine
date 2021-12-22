//
// Created by jeditux on 19.10.2021.
//

#include "Core/Application.h"
#include "Core/Log.h"
#include "Window.h"

namespace Core {

    Application::Application() {
        LOG_INFO("Starting Application");
    }

    Application::~Application() {
        LOG_INFO("Closing Application");
    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char *title) {
        m_pWindow = std::make_unique<Window>(title, window_width, window_height);
        m_pWindow->set_event_callback([](Event& event) {
            LOG_INFO("[EVENT] Changed size to {0}x{1}", event.width, event.height);
        });

        while (!m_pWindow->getWindowClose())
        {
            m_pWindow->on_update();
            on_update();
        }
        return 0;
    }
}
