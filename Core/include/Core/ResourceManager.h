#pragma once

#include <string>
#include <memory>
#include <map>

namespace Rendering {
    class ShaderProgram;
}

namespace Core {
    class ResourceManager {
    public:
        explicit ResourceManager(const std::string& executablePath);
        ~ResourceManager() = default;

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
        ResourceManager(ResourceManager&&) = delete;
        ResourceManager& operator=(ResourceManager&&) = delete;

        std::shared_ptr<Rendering::ShaderProgram> loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
        std::shared_ptr<Rendering::ShaderProgram> getShader(const std::string& shaderName) const;

    private:
        const std::string RESOURCES_PATH = "res/";
        const std::string SHADERS_PATH = "shaders/";

        std::string m_path;

        typedef std::map<std::string, std::shared_ptr<Rendering::ShaderProgram>> ShaderProgramsMap;
        ShaderProgramsMap m_shaderPrograms;

        std::string getFileData(const std::string& fileName) const;
    };
}