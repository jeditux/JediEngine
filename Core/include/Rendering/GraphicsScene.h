//
// Created by Anatoliy on 01.06.2022.
//

#pragma once

#include <memory>
//#include "ShaderProgram.h"
//#include "Texture2D.h"
#include "Core/ResourceManager.h"
#include "Camera.h"


namespace Rendering {
    class GraphicsScene {
    public:
        GraphicsScene(std::string executablePath);
        void render();

        std::array<float, 4>& backgroundColor();
        Camera& camera();

    private:
        std::shared_ptr<Rendering::ShaderProgram> m_pShaderProgram;
        std::shared_ptr<Rendering::ShaderProgram> m_pTextureShader;
        std::shared_ptr<Rendering::Texture2D> m_pContainerTexture;
        std::shared_ptr<Rendering::Texture2D> m_pSmileTexture;
        unsigned int m_vao;
        std::unique_ptr<Core::ResourceManager> m_pResourceManager;

        std::array<float, 4> m_backgroundColor;

        std::string m_executablePath;

        Camera m_camera;
    };
}
