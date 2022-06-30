//
// Created by jeditux on 19.10.2021.
//

#include "Core/Application.h"
#include "Core/Log.h"
#include "Window.h"

namespace Core {

    Application::Application(std::string executablePath)
        : m_executablePath(std::move(executablePath)) {
        LOG_INFO("Starting Application");
    }

    Application::~Application() {
        LOG_INFO("Closing Application");
    }

    std::shared_ptr<Rendering::GraphicsScene> Application::scene() {
        return m_pScene;
    }

    std::shared_ptr<Rendering::GuiManager> Application::gui() {
        return m_pGuiManager;
    }

    void Application::setupUI() {
    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char *title) {
        m_pWindow = std::make_unique<Window>(title, window_width, window_height, m_executablePath);
        m_pWindow->setExecutablePath(m_executablePath);
        m_pScene = std::make_shared<Rendering::GraphicsScene>(m_executablePath, std::make_pair(window_width, window_height));
        m_pGuiManager = std::make_shared<Rendering::GuiManager>(m_pWindow->getRawPtr(), window_width, window_height);
        setupUI();
        m_dispatcher.addEventHandler<ResizeEvent>([](ResizeEvent& event) {
            LOG_INFO("[EVENT] Changed size to {0}x{1}", event.width, event.height);
        });
        m_dispatcher.addEventHandler<MouseMoveEvent>([this](MouseMoveEvent& event) {
//            LOG_INFO("[EVENT] Mouse moved to {0}x{1}", event.x, event.y);
            onMouseMove(event);
        });
        m_dispatcher.addEventHandler<MouseButtonPressEvent>([this](MouseButtonPressEvent& event) {
            onMousePress(event);
        });
        m_dispatcher.addEventHandler<KeyPressEvent>([this](KeyPressEvent& event) {
            onKeyPress(event);
        });
        m_dispatcher.addEventHandler<KeyReleaseEvent>([this](KeyReleaseEvent& event) {
            onKeyRelease(event);
        });
        m_pWindow->setEventCallback([&](BaseEvent& event) {
            m_dispatcher.dispatch(event);
        });
        m_pWindow->setRenderFunction([&]() {
            m_pScene->render();
            m_pGuiManager->render();
        });

        while (!m_pWindow->getWindowClose())
        {
            m_pWindow->render();
            on_update();
        }
        return 0;
    }
}
