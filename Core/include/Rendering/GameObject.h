//
// Created by jeditux on 23.06.2022.
//

#pragma once

#include <memory>
#include <array>
#include "glm/vec3.hpp"
#include "Camera.h"

namespace Rendering {
    class ShaderProgram;

    class GameObject {
    public:
        virtual void render() const = 0;
        virtual std::shared_ptr<ShaderProgram>& shader() = 0;
    };

    class LightSource : public GameObject {
    public:
        LightSource(std::shared_ptr<ShaderProgram>& shaderProgram);
        void render() const override;
        std::shared_ptr<ShaderProgram>& shader() override;
        std::array<float, 3>& color();
        glm::vec3& position();
    private:
        std::shared_ptr<ShaderProgram> m_pShader;
        unsigned int m_VBO;
        unsigned int m_VAO;
        glm::vec3 m_pos;
        std::array<float, 3> m_color;
    };

    class Cube : public GameObject {
    public:
        Cube(std::shared_ptr<ShaderProgram>& shaderProgram, LightSource& lightSource, Camera& camera);
        void render() const override;
        std::shared_ptr<ShaderProgram>& shader() override;
        std::array<float, 3>& color();
        glm::vec3& position();
    private:
        std::shared_ptr<ShaderProgram> m_pShader;
        unsigned int m_VBO;
        unsigned int m_VAO;
        glm::vec3 m_pos;
        std::array<float, 3> m_color;
        std::array<float, 3> m_lightColor;
        glm::vec3& m_lightPos;
        glm::vec3& m_cameraPos;
    };
}
