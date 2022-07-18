//
// Created by Anatoliy on 11.06.2022.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rendering {
    const glm::vec3 WORLD_TOP = {0.0f, 1.0f, 0.0f};

    enum class ProjectionMode {
        PERSPECTIVE,
        ORTHO
    };

    class Camera {
    public:
        Camera(std::pair<size_t, size_t> viewportSize, glm::vec3 position = {0.0f, 0.0f, 0.0f }, glm::vec3 direction = {2.0f, 1.0f, 5.0f}, glm::vec3 up = {0.0f, 1.0f, 0.0f});
        void moveTo(glm::vec3 position);
        glm::vec3& position();
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;
        void moveFront(float distance);
        void moveBack(float distance);
        void moveLeft(float distance);
        void moveRight(float distance);
        void rotate(float yaw, float pitch);
        void setProjectionMode(ProjectionMode projectionMode);
    private:
        std::pair<size_t, size_t> m_viewportSize;
        glm::vec3 m_position;

        float m_yaw;
        float m_pitch;

        glm::vec3 m_front;
        glm::vec3 m_right;
        glm::vec3 m_up;

        ProjectionMode m_projectionMode;

        void updateCameraVectors();
    };
}
