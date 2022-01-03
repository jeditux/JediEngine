//
// Created by jeditux on 1/2/22.
//

#pragma once

#include <string>
#include <glad/glad.h>

namespace Rendering {
    class ShaderProgram {
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ~ShaderProgram();
        void use() const;
        bool isCompiled() const {return m_isCompiled; }

    private:
        bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderId);
        bool m_isCompiled = false;
        GLuint m_Id = 0;
    };
}
