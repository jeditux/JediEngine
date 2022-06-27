//
// Created by Anatoliy on 01.06.2022.
//

#include "Rendering/GraphicsScene.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Rendering/ShaderProgram.h"
#include "Rendering/Texture2D.h"
#include "Rendering/Camera.h"

namespace Rendering {

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    GraphicsScene::GraphicsScene(std::string executablePath) : m_executablePath(std::move(executablePath)) {
        m_pResourceManager = std::make_unique<Core::ResourceManager>(m_executablePath);
        m_pLightShader = m_pResourceManager->loadShader("light", "light.vert", "light.frag");
        m_pCubeShader = m_pResourceManager->loadShader("cube", "cube.vert", "cube.frag");

        m_backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f};
        m_objectColor = {1.0f, 0.5f, 0.31f};
        m_lightColor = {1.0f, 1.0f, 1.0f};

        m_light = std::make_shared<LightSource>(m_pLightShader);
        m_cube = std::make_shared<Cube>(m_pCubeShader);

        glEnable(GL_DEPTH_TEST);
    }

    Camera& GraphicsScene::camera() {
        return m_camera;
    }

    std::array<float, 3>& GraphicsScene::lightColor() {
        return m_lightColor;
    }

    std::array<float, 3>& GraphicsScene::objectColor() {
        return m_objectColor;
    }

    void GraphicsScene::render() {
        glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_cube->shader()->use();
        m_cube->shader()->setVec3("objectColor", m_objectColor[0], m_objectColor[1], m_objectColor[2]);
        m_cube->shader()->setVec3("lightColor", m_lightColor[0], m_lightColor[1], m_lightColor[2]);
        m_cube->shader()->setVec3("lightPos", lightPos[0], lightPos[1], lightPos[2]);
        m_cube->shader()->setVec3("viewPos", m_camera.position()[0], m_camera.position()[1], m_camera.position()[2]);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 1.0f, 100.0f);
        glm::mat4 view = m_camera.getViewMatrix();
        m_cube->shader()->setMatrix("projection", glm::value_ptr(projection));
        m_cube->shader()->setMatrix("view", glm::value_ptr(view));

        glm::mat4 model = glm::mat4(1.0f);
        m_cube->shader()->setMatrix("model", glm::value_ptr(model));
        m_cube->render();

        m_light->shader()->use();
        m_light->shader()->setMatrix("projection", glm::value_ptr(projection));
        m_light->shader()->setMatrix("view", glm::value_ptr(view));
        m_light->shader()->setVec3("lightColor", m_lightColor[0], m_lightColor[1], m_lightColor[2]);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        m_light->shader()->setMatrix("model", glm::value_ptr(model));
        m_light->render();
    }

    std::array<float, 4>& GraphicsScene::backgroundColor() {
        return m_backgroundColor;
    }
}
