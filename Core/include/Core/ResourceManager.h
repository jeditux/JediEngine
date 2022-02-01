#pragma once

#include <string>
#include <memory>
#include <map>

namespace Rendering {
    class ShaderProgram;
    class Texture2D;
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

        std::shared_ptr<Rendering::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
        std::shared_ptr<Rendering::Texture2D> getTexture(const std::string& textureName) const;

    private:
        const std::string RESOURCES_PATH = "res/";
        const std::string SHADERS_PATH = "shaders/";
        const std::string TEXTURES_PATH = "textures/";

        std::string m_path;

        typedef std::map<std::string, std::shared_ptr<Rendering::ShaderProgram>> ShaderProgramsMap;
        ShaderProgramsMap m_shaderPrograms;

        typedef std::map<std::string, std::shared_ptr<Rendering::Texture2D>> TexturesMap;
        TexturesMap m_textures;

        std::string getFileData(const std::string& fileName) const;
    };
}