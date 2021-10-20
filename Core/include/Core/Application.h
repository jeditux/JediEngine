//
// Created by jeditux on 19.10.2021.
//

#pragma once

#include <memory>

namespace JediEngine {
    class Application {
    public:
        Application();
        virtual ~Application();

        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        virtual int start(unsigned int width, unsigned int height, const char* title);
        virtual void on_update() {}

    private:
        std::unique_ptr<class Window> m_pWindow;
    };
}
