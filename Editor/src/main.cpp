//
// Created by jeditux on 19.10.2021.
//

#include <iostream>
#include <memory>
#include "Core/Application.h"

class MyApp : public Core::Application {
public:
    void on_update() override {
//        std::cout << "Update frame: " << frame++ << std::endl;
    }

private:
    int frame = 0;
};

int main() {
    auto myApp = std::make_unique<MyApp>();
    return myApp->start(1024, 768, "My first App");
}
