//
// Created by jeditux on 7/12/22.
//

#include "Rendering/Sprite.h"
#include "glm/gtc/type_ptr.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Rendering {
    Sprite::Sprite(const std::shared_ptr<ShaderProgram>& pShader, const std::shared_ptr<Texture2D>& pTexture
            , const glm::vec2& position, const glm::vec2& size, float rotation)
        : m_pShader(pShader), m_pTexture(pTexture), m_position(position), m_size(size), m_rotation(rotation) {

        const GLfloat vertices[] = {
                // 2--3    1
                // | /   / |
                // 1    3--2

                // X  Y
                0.f, 0.f,
                0.f, 1.f,
                1.f, 1.f,
                1.f, 1.f,
                1.f, 0.f,
                0.f, 0.f
        };

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_vertexCoordsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glGenBuffers(1, &m_textureCoordsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Sprite::~Sprite() {
        glDeleteBuffers(1, &m_vertexCoordsVBO);
        glDeleteBuffers(1, &m_textureCoordsVBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void Sprite::setPosition(glm::vec2& position) {
        m_position = position;
    }

    void Sprite::setSize(glm::vec2& size) {
        m_size = size;
    }

    void Sprite::setRotation(float rotation) {
        m_rotation = rotation;
    }

    std::shared_ptr<ShaderProgram>& Sprite::shader() {
        return m_pShader;
    }

    void Sprite::render() const {
        m_pShader->use();

        glm::mat4 model(1.f);
        model = glm::translate(model, glm::vec3(m_position.x, m_position.y, 0));
        model = glm::rotate(model, m_rotation, glm::vec3(0.f, 0.f, 1.f));
        model = glm::scale(model, glm::vec3(m_size.x, m_size.y, 0.f));
        m_pShader->setMatrix("model", glm::value_ptr(model));

        glBindVertexArray(m_VAO);
        glActiveTexture(GL_TEXTURE0);
        m_pTexture->bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}
