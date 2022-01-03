#include "Core/ResourceManager.h"
#include "Core/Log.h"
#include "Rendering/ShaderProgram.h"
#include <fstream>
#include <sstream>

namespace Core {
    ResourceManager::ResourceManager(const std::string& executablePath) {
        size_t lastSlashPos = executablePath.find_last_of("/\\");
        m_path = executablePath.substr(0, lastSlashPos);
    }

    std::shared_ptr<Rendering::ShaderProgram> ResourceManager::loadShader(const std::string &shaderName,
                                                                          const std::string &vertexPath,
                                                                          const std::string &fragmentPath) {
        std::string vertexShaderSource = getFileData(SHADERS_PATH + vertexPath);
        if (vertexShaderSource.empty()) {
            LOG_WARN("No vertex shader!");
            return nullptr;
        }

        std::string fragmentShaderSource = getFileData(SHADERS_PATH + fragmentPath);
        if (fragmentShaderSource.empty()) {
            LOG_WARN("No fragment shader!");
            return nullptr;
        }

        auto [it, isNew] = m_shaderPrograms.try_emplace(shaderName, std::make_shared<Rendering::ShaderProgram>(vertexShaderSource, fragmentShaderSource));
        if (!it->second->isCompiled()) {
            LOG_WARN("Can't load shader program!\nVertex shader path: {0}\nFragment shader path: {1}", vertexPath, fragmentPath);
            return nullptr;
        }
        return it->second;
    }

    std::shared_ptr<Rendering::ShaderProgram> ResourceManager::getShader(const std::string &shaderName) const {
        if (m_shaderPrograms.count(shaderName) == 0) {
            LOG_WARN("Can't find shader program: {0}", shaderName);
            return nullptr;
        }
        return m_shaderPrograms.at(shaderName);
    }

    std::string ResourceManager::getFileData(const std::string &fileName) const {
        std::ifstream vertexInput(m_path + "/" + RESOURCES_PATH + fileName);
        if (!vertexInput.is_open()) {
            LOG_WARN("Failed to open file: {0}", fileName);
            return "";
        }
        std::stringstream buffer;
        buffer << vertexInput.rdbuf();
        return buffer.str();
    }
}