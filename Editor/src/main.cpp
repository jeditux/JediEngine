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
        gui()->addColorPicker4("Background Color", scene()->backgroundColor());
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
};

int main(int argc, char** argv) {
    auto myApp = std::make_unique<MyApp>(argv[0]);
    return myApp->start(1024, 768, "My first App");
}
