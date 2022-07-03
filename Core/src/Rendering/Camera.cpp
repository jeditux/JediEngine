//
// Created by Anatoliy on 11.06.2022.
//

#include "Rendering/Camera.h"

namespace Rendering {
    Camera::Camera(std::pair<size_t, size_t> viewportSize, glm::vec3 position, glm::vec3 target, glm::vec3 up)
        : m_viewportSize(std::move(viewportSize))
        , m_position(position)
        , m_yaw(-90.0f)
        , m_pitch(0.0f) {
        updateCameraVectors();
    }

    void Camera::moveTo(glm::vec3 position) {
        m_position = position;
    }

    glm::vec3& Camera::position() {
        return m_position;
    }

    glm::mat4 Camera::getViewMatrix() const {
        glm::vec3 target = m_position + m_front;
        return glm::lookAt(m_position, target, m_up);
    }

    glm::mat4 Camera::getProjectionMatrix() const {
        return glm::perspective(glm::radians(45.0f), static_cast<float>(m_viewportSize.first) / m_viewportSize.second, 1.0f, 100.0f);
    }

    void Camera::moveFront(float distance) {
        m_position += m_front * distance;
    }

    void Camera::moveBack(float distance) {
        m_position -= m_front * distance;
    }

    void Camera::moveLeft(float distance) {
        m_position -= m_right * distance;
    }

    void Camera::moveRight(float distance) {
        m_position += m_right * distance;
    }

    void Camera::rotate(float yaw, float pitch) {
        m_yaw += yaw;
        m_pitch += pitch;
        updateCameraVectors();
    }

    void Camera::updateCameraVectors() {
        glm::vec3 tmpFront;
        tmpFront.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        tmpFront.y = sin(glm::radians(m_pitch));
        tmpFront.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(tmpFront);
        m_right = glm::normalize(glm::cross(m_front, WORLD_TOP));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }
}
