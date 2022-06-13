//
// Created by Anatoliy on 11.06.2022.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rendering {
    class Camera {
    public:
        Camera(glm::vec3 position = {0.0f, 0.0f, 0.0f }, glm::vec3 direction = {0.0f, 0.0f, 0.0f}, glm::vec3 top = {0.0f, 1.0f, 0.0f});
        void moveTo(glm::vec3 position);
        void lookAt(glm::vec3 target);
        glm::vec3& position();
        glm::mat4 getViewMatrix() const;
    private:
        glm::vec3 m_position;
        glm::vec3 m_target;
        glm::vec3 m_top;
    };
}
