//
// Created by Anatoliy on 02.06.2022.
//

#pragma once

struct GLFWwindow;

namespace Rendering {

    class GuiManager {
    public:
        void init(GLFWwindow* window, unsigned int width, unsigned int height);
        bool isEnabled() const;
        void setEnabled(bool value);
        void render();

    private:
        bool m_isEnabled;
        unsigned int m_width;
        unsigned int m_height;
    };
}
