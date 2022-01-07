//
// Created by jeditux on 1/2/22.
//

#include "Rendering/ShaderProgram.h"
#include "Core/Log.h"

namespace Rendering {
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
        GLuint vertexShaderId;
        if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderId)) {
            LOG_CRITICAL("Vertex shader compile time error");
            return;
        }

        unsigned int fragmentShaderId;
        if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderId)) {
            LOG_CRITICAL("Fragment shader compile time error");
            return;
        }

        m_Id = glCreateProgram();
        glAttachShader(m_Id, vertexShaderId);
        glAttachShader(m_Id, fragmentShaderId);
        glLinkProgram(m_Id);

        GLint success;
        glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[1024];
            glGetProgramInfoLog(m_Id, 1024, nullptr, infoLog);
            LOG_CRITICAL("ERROR::SHADER: Link time error:\n{0}", infoLog);
        } else {
            m_isCompiled = true;
        }

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_Id);
    }

    void ShaderProgram::use() const {
        glUseProgram(m_Id);
    }

    bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderId) {
        shaderId = glCreateShader(shaderType);
        const char* cSource = source.c_str();
        glShaderSource(shaderId, 1, &cSource, nullptr);
        glCompileShader(shaderId);

        GLint success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
            LOG_CRITICAL("ERROR::SHADER: Compile time error:\n{0}", infoLog);
            return false;
        }
        return true;
    }

    void ShaderProgram::setUniform4f(const std::string &name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4) const {
        glUniform4f(glGetUniformLocation(m_Id, name.c_str()), f1, f2, f3, f4);
    }

    void ShaderProgram::setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(m_Id, name.c_str()), static_cast<int>(value));
    }

    void ShaderProgram::setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(m_Id, name.c_str()), value);
    }

    void ShaderProgram::setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(m_Id, name.c_str()), value);
    }
}

