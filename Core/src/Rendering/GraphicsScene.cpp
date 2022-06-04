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

namespace Rendering {

    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    GraphicsScene::GraphicsScene(std::string executablePath) : m_executablePath(std::move(executablePath)) {
        m_pResourceManager = std::make_unique<Core::ResourceManager>(m_executablePath);
        m_pShaderProgram = m_pResourceManager->loadShader("triangle", "triangle.vert", "triangle.frag");
        m_pContainerTexture = m_pResourceManager->loadTexture("container", "container.jpg");
        m_pSmileTexture = m_pResourceManager->loadTexture("smile", "awesomeface.png");

        unsigned int VBO, EBO;
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);

        m_pTextureShader = m_pResourceManager->loadShader("texture", "texture.vert", "texture.frag");
        m_pTextureShader->use();
        glActiveTexture(GL_TEXTURE0);
        m_pContainerTexture->bind();
        m_pTextureShader->setInt("texture1", 0);

        glActiveTexture(GL_TEXTURE1);
        m_pSmileTexture->bind();
        m_pTextureShader->setInt("texture2", 1);

        glm::mat4 trans = glm::mat4(1.0);
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        m_pTextureShader->setMatrix("transform", glm::value_ptr(trans));

        m_backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f};
    }

    void GraphicsScene::render() {
        glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        m_pContainerTexture->bind();
        glActiveTexture(GL_TEXTURE1);
        m_pSmileTexture->bind();
        m_pTextureShader->use();
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    std::array<float, 4>& GraphicsScene::backgroundColor() {
        return m_backgroundColor;
    }
}
