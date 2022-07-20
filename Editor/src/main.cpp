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
        auto w = Rendering::WidgetFactory::window("Control Panel", 0, 0, 500, 400);
        w->addChildWidget(Rendering::WidgetFactory::colorEdit4("Background Color", scene()->backgroundColor()))
            .addChildWidget(Rendering::WidgetFactory::spacing())
            .addChildWidget(Rendering::WidgetFactory::text("Cam Position"))
            .addChildWidget(Rendering::WidgetFactory::inputNumber("X", scene()->camera().position()[0], m_camPosStep))
            .addChildWidget(Rendering::WidgetFactory::inputNumber("Y", scene()->camera().position()[1], m_camPosStep))
            .addChildWidget(Rendering::WidgetFactory::inputNumber("Z", scene()->camera().position()[2], m_camPosStep))
            .addChildWidget(Rendering::WidgetFactory::spacing())
            .addChildWidget(Rendering::WidgetFactory::colorEdit3("Object Color", m_cube->color()))
            .addChildWidget(Rendering::WidgetFactory::colorEdit3("Light Color", m_lightSource->color()));
          gui()->addWidget(w);
    }

    void setupScene() override {
        m_pLightShader = resourceManager()->loadShader("light", "light.vert", "light.frag");
        m_pCubeShader = resourceManager()->loadShader("cube", "cube.vert", "cube.frag");
        m_pSpriteShader = resourceManager()->loadShader("sprite", "sprite.vert", "sprite.frag");
        m_pSmileTexture = resourceManager()->loadTexture("smile", "awesomeface.png");
        m_smilingSprite = std::make_shared<Rendering::Sprite>(m_pSpriteShader, m_pSmileTexture, glm::vec2(300.f, 200.f), glm::vec2(100.f), 180.f);

        scene()->camera().position() = {0.0f, 0.0f, 8.0f};
        scene()->camera().setProjectionMode(Rendering::ProjectionMode::PERSPECTIVE);

        m_lightSource = std::make_shared<Rendering::LightSource>(m_pLightShader);
        m_lightSource->position() = glm::vec3(1.2f, 1.0f, 2.0f);
        scene()->addGameObject(m_lightSource);

        m_cube = std::make_shared<Rendering::Cube>(m_pCubeShader, *m_lightSource, scene()->camera());
        m_cube->position() = glm::vec3(0.f, 0.f, 0.f);
        scene()->addGameObject(m_cube);
    }

    void on_update() override {
//        std::cout << "Update frame: " << frame++ << std::endl;
    }

    void onMouseMove(Core::MouseMoveEvent& event) override {
//        std::cout << "Mouse moved to " << event.x << "x" << event.y << std::endl;
        int xOffset = event.x - m_lastPosX;
        int yOffset = event.y - m_lastPosY;
        m_lastPosX = event.x;
        m_lastPosY = event.y;
//        scene()->camera().rotate(0.05f * xOffset, 0.05f * yOffset);
    }

    void onMousePress(Core::MouseButtonPressEvent& event) override {
        std::cout << "Mouse pressed " << event.x << "x" << event.y << std::endl;
    }

    void onKeyPress(Core::KeyPressEvent& event) override {
        switch (event.key) {
            case Core::Key::UP:
                scene()->camera().moveFront(0.1f);
                break;
            case Core::Key::DOWN:
                scene()->camera().moveBack(0.1f);
                break;
            case Core::Key::LEFT:
                scene()->camera().moveLeft(0.1f);
                break;
            case Core::Key::RIGHT:
                scene()->camera().moveRight(0.1f);
                break;
            case Core::Key::UNSUPPORTED:
                std::cout << "Key pressed " << static_cast<int>(event.key) << std::endl;
                break;
        }
    }

private:
    int frame = 0;
    float m_camPosStep = 0.1f;
    int m_lastPosX = 0;
    int m_lastPosY = 0;

    std::shared_ptr<Rendering::ShaderProgram> m_pLightShader;
    std::shared_ptr<Rendering::ShaderProgram> m_pCubeShader;
    std::shared_ptr<Rendering::ShaderProgram> m_pSpriteShader;
    std::shared_ptr<Rendering::Sprite> m_smilingSprite;

    std::shared_ptr<Rendering::Texture2D> m_pSmileTexture;

    std::shared_ptr<Rendering::Cube> m_cube;
    std::shared_ptr<Rendering::LightSource> m_lightSource;
};

int main(int argc, char** argv) {
    auto myApp = std::make_unique<MyApp>(argv[0]);
    return myApp->start(1024, 768, "My first App");
}
