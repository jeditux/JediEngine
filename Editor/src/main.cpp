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
        gui()->colorPicker4("Background Color", scene()->backgroundColor());
        scene()->camera().position() = {2.0f, 2.0f, 8.0f};
        gui()->inputNumber("Cam Position X", scene()->camera().position()[0], m_camPosStep);
        gui()->inputNumber("Cam Position Y", scene()->camera().position()[1], m_camPosStep);
        gui()->inputNumber("Cam Position Z", scene()->camera().position()[2], m_camPosStep);
        gui()->colorPicker3("Object Color", scene()->objectColor());
        gui()->colorPicker3("Light Color", scene()->lightColor());
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

private:
    int frame = 0;
    float m_camPosStep = 0.1f;
};

int main(int argc, char** argv) {
    auto myApp = std::make_unique<MyApp>(argv[0]);
    return myApp->start(1024, 768, "My first App");
}
