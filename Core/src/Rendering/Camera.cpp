//
// Created by Anatoliy on 11.06.2022.
//

#include "Rendering/Camera.h"

namespace Rendering {
    Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 top)
        : m_position(position)
        , m_target(target)
        , m_top(top) {
    }

    void Camera::moveTo(glm::vec3 position) {
        m_position = position;
    }

    void Camera::lookAt(glm::vec3 target) {
        m_target = target;
    }

    glm::vec3& Camera::position() {
        return m_position;
    }

    glm::mat4 Camera::getViewMatrix() const {
        return glm::lookAt(m_position, m_target, m_top);
    }
}
