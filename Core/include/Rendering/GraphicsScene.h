//
// Created by Anatoliy on 01.06.2022.
//

#pragma once

#include <memory>
#include "Core/ResourceManager.h"
#include "Camera.h"
#include "GameObject.h"


namespace Rendering {
    class ShaderProgram;
    class Texture2D;
    class Cube;

    class GraphicsScene {
    public:
        GraphicsScene(std::string executablePath, std::pair<size_t, size_t> windowSize);
        void render();

        std::array<float, 4>& backgroundColor();
        Camera& camera();

        std::array<float, 3>& lightColor();
        std::array<float, 3>& objectColor();

    private:
        std::shared_ptr<Rendering::ShaderProgram> m_pShaderProgram;
        std::shared_ptr<Rendering::ShaderProgram> m_pTextureShader;
        std::shared_ptr<Rendering::Texture2D> m_pContainerTexture;
        std::shared_ptr<Rendering::Texture2D> m_pSmileTexture;
        std::unique_ptr<Core::ResourceManager> m_pResourceManager;
        std::shared_ptr<Rendering::ShaderProgram> m_pLightShader;
        std::shared_ptr<Rendering::ShaderProgram> m_pCubeShader;

        std::array<float, 4> m_backgroundColor;
        std::array<float, 3> m_objectColor;
        std::array<float, 3> m_lightColor;

        std::string m_executablePath;

        Camera m_camera;
        std::shared_ptr<LightSource> m_light;
        std::shared_ptr<Cube> m_cube;
    };
}
