//
// Created by jeditux on 23.06.2022.
//

#pragma once

#include <memory>
#include "glm/vec3.hpp"

namespace Rendering {
    class ShaderProgram;

    class GameObject {
    public:
        GameObject(std::shared_ptr<ShaderProgram>& shaderProgram);
        virtual void render() const;
        std::shared_ptr<ShaderProgram>& shader();
        glm::vec3& position();
        std::array<float, 3>& color();
        virtual ~GameObject();
    protected:
        std::shared_ptr<ShaderProgram> m_pShader;
        unsigned int m_VBO;
        unsigned int m_VAO;
    };

    class Cube : public GameObject {
    public:
        Cube(std::shared_ptr<ShaderProgram>& shaderProgram);
    };

    class LightSource : public GameObject {
    public:
        LightSource(std::shared_ptr<ShaderProgram>& shaderProgram);
    };
}
