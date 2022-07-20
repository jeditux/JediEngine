//
// Created by Anatoliy on 01.06.2022.
//

#include "Rendering/GraphicsScene.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Rendering/ShaderProgram.h"
#include "Rendering/Camera.h"

namespace Rendering {

    GraphicsScene::GraphicsScene(std::string executablePath, std::pair<size_t, size_t> windowSize)
        : m_executablePath(std::move(executablePath)), m_camera(windowSize)
        , m_backgroundColor({0.f, 0.f, 0.f, 0.f}){
        glEnable(GL_DEPTH_TEST);
    }

    Camera& GraphicsScene::camera() {
        return m_camera;
    }

    void GraphicsScene::addGameObject(const std::shared_ptr<GameObject>& gameObject) {
        m_gameObjects.push_back(gameObject);
    }

    void GraphicsScene::render() {
        glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = m_camera.getProjectionMatrix();
        glm::mat4 view = m_camera.getViewMatrix();
        for (const auto& go : m_gameObjects) {
            go->shader()->use();
            go->shader()->setMatrix("projection", glm::value_ptr(projection));
            go->shader()->setMatrix("view", glm::value_ptr(view));
            go->render();
        }
    }

    std::array<float, 4>& GraphicsScene::backgroundColor() {
        return m_backgroundColor;
    }
}
