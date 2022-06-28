//
// Created by jeditux on 19.10.2021.
//

#pragma once

#include <string>
#include <memory>
#include "Event.h"
#include "Rendering/GraphicsScene.h"
#include "Rendering/GuiManager.h"

namespace Core {
    class Application {
    public:
        Application(std::string executablePath);
        virtual ~Application();

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        virtual void setupUI();
        virtual int start(unsigned int width, unsigned int height, const char* title);
        virtual void on_update() {}

        virtual void onMouseMove(MouseMoveEvent& event) {}
        virtual void onMousePress(MouseButtonPressEvent& event) {}
        virtual void onMouseRelease(MouseButtonReleaseEvent& event) {}
        virtual void onKeyPress(KeyPressEvent& event) {}
        virtual void onKeyRelease(KeyReleaseEvent& event) {}

    protected:
        std::shared_ptr<Rendering::GraphicsScene> scene();
        std::shared_ptr<Rendering::GuiManager> gui();
    private:
        std::unique_ptr<class Window> m_pWindow;
        EventDispatcher m_dispatcher;
        std::string m_executablePath;
        std::shared_ptr<Rendering::GraphicsScene> m_pScene;
        std::shared_ptr<Rendering::GuiManager> m_pGuiManager;
    };
}
