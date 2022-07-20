//
// Created by Anatoliy on 01.06.2022.
//

#pragma once

#include <memory>
#include <array>
#include <vector>
#include "Core/ResourceManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Sprite.h"


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

        void addGameObject(const std::shared_ptr<GameObject>& gameObject);

    private:
        std::string m_executablePath;
        std::array<float, 4> m_backgroundColor;
        Camera m_camera;
        std::vector<std::shared_ptr<GameObject>> m_gameObjects;
    };
}
