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

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
    };

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    GraphicsScene::GraphicsScene(std::string executablePath) : m_executablePath(std::move(executablePath)) {
        m_pResourceManager = std::make_unique<Core::ResourceManager>(m_executablePath);
        m_pLightShader = m_pResourceManager->loadShader("light", "light.vert", "light.frag");
        m_pCubeShader = m_pResourceManager->loadShader("cube", "cube.vert", "cube.frag");

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &m_cubeVAO);
        glBindVertexArray(m_cubeVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glGenVertexArrays(1, &m_lightVAO);
        glBindVertexArray(m_lightVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        m_backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f};
        m_objectColor = {1.0f, 0.5f, 0.31f};
        m_lightColor = {1.0f, 1.0f, 1.0f};

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

        m_pCubeShader->use();
        m_pCubeShader->setVec3("objectColor", m_objectColor[0], m_objectColor[1], m_objectColor[2]);
        m_pCubeShader->setVec3("lightColor", m_lightColor[0], m_lightColor[1], m_lightColor[2]);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 1.0f, 100.0f);
        glm::mat4 view = m_camera.getViewMatrix();

        m_pCubeShader->setMatrix("projection", glm::value_ptr(projection));
        m_pCubeShader->setMatrix("view", glm::value_ptr(view));

        glm::mat4 model = glm::mat4(1.0f);
        m_pCubeShader->setMatrix("model", glm::value_ptr(model));

        glBindVertexArray(m_cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        m_pLightShader->use();
        m_pLightShader->setMatrix("projection", glm::value_ptr(projection));
        m_pLightShader->setMatrix("view", glm::value_ptr(view));
        m_pLightShader->setVec3("lightColor", m_lightColor[0], m_lightColor[1], m_lightColor[2]);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        m_pLightShader->setMatrix("model", glm::value_ptr(model));

        glBindVertexArray(m_lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    std::array<float, 4>& GraphicsScene::backgroundColor() {
        return m_backgroundColor;
    }
}
