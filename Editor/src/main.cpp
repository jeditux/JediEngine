//
// Created by jeditux on 19.10.2021.
//

#include <iostream>
#include <memory>
#include "Core/Application.h"

class MyApp : public Core::Application {
public:
    MyApp(const std::string& path) : Core::Application(path) {
    }

    void setupUI() override {
        gui()->setEnabled(true);
        scene()->camera().position() = {2.0f, 2.0f, 8.0f};
        auto w = Rendering::WidgetFactory::window("Control Panel", 0, 0, 500, 400);
        w->addChildWidget(Rendering::WidgetFactory::colorEdit4("Background Color", scene()->backgroundColor()))
            .addChildWidget(Rendering::WidgetFactory::spacing())
            .addChildWidget(Rendering::WidgetFactory::text("Cam Position"))
            .addChildWidget(Rendering::WidgetFactory::inputNumber("X", scene()->camera().position()[0], m_camPosStep))
            .addChildWidget(Rendering::WidgetFactory::inputNumber("Y", scene()->camera().position()[1], m_camPosStep))
            .addChildWidget(Rendering::WidgetFactory::inputNumber("Z", scene()->camera().position()[2], m_camPosStep))
            .addChildWidget(Rendering::WidgetFactory::spacing())
            .addChildWidget(Rendering::WidgetFactory::colorEdit3("Object Color", scene()->objectColor()))
            .addChildWidget(Rendering::WidgetFactory::colorEdit3("Light Color", scene()->lightColor()));
          gui()->addWidget(w);
    }

    void on_update() override {
//        std::cout << "Update frame: " << frame++ << std::endl;
    }

    void onMouseMove(Core::MouseMoveEvent& event) override {
//        std::cout << "Mouse moved to " << event.x << "x" << event.y << std::endl;
    }

    void onMousePress(Core::MouseButtonPressEvent& event) override {
        std::cout << "Mouse pressed " << event.x << "x" << event.y << std::endl;
    }

    void onKeyPress(Core::KeyPressEvent& event) override {
        std::cout << "Key pressed " << static_cast<int>(event.key) << std::endl;
    }

private:
    int frame = 0;
    float m_camPosStep = 0.1f;
};

int main(int argc, char** argv) {
    auto myApp = std::make_unique<MyApp>(argv[0]);
    return myApp->start(1024, 768, "My first App");
}
