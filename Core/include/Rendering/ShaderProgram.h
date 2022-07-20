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

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        void use() const;
        bool isCompiled() const {return m_isCompiled; }
        void setUniform4f(const std::string& name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4) const;
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMatrix(const std::string& name, const GLfloat* value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;

    private:
        bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderId);
        bool m_isCompiled = false;
        GLuint m_Id = 0;
    };
}
