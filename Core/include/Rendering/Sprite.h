//
// Created by jeditux on 7/12/22.
//

#pragma once

#include <memory>
#include "ShaderProgram.h"
#include "glm/vec2.hpp"
#include "Texture2D.h"
#include "GameObject.h"

namespace Rendering {
    class Sprite : public GameObject {
    public:
        Sprite(const std::shared_ptr<ShaderProgram>& pShader, const std::shared_ptr<Texture2D>& pTexture
               , const glm::vec2& position = glm::vec2(0.f), const glm::vec2& size = glm::vec2(1.f), float rotation = 0.f);
        ~Sprite();
        void setPosition(glm::vec2& position);
        void setSize(glm::vec2& size);
        void setRotation(float rotation);
        void render() const override;
        std::shared_ptr<ShaderProgram>& shader() override;
    private:
        std::shared_ptr<ShaderProgram> m_pShader;
        std::shared_ptr<Texture2D> m_pTexture;
        glm::vec2 m_position;
        glm::vec2 m_size;
        float m_rotation;

        GLuint m_vertexCoordsVBO;
        GLuint m_textureCoordsVBO;
        GLuint m_VAO;
    };
}
