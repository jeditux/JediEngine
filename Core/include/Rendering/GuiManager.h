//
// Created by Anatoliy on 02.06.2022.
//

#pragma once

#include <vector>
#include <memory>
#include <string>

struct GLFWwindow;

namespace Rendering {

    class Widget {
    public:
        virtual void render() = 0;
    };

    class ColorPicker4 : public Widget {
    public:
        ColorPicker4(std::string label, std::array<float, 4>& value);
        void render() override;
    private:
        std::string m_label;
        std::array<float, 4>& m_value;
    };

    class GuiManager {
    public:
        GuiManager(GLFWwindow* window, unsigned int width, unsigned int height);
        bool isEnabled() const;
        void setEnabled(bool value);
        void render();

        void addColorPicker4(std::string label, std::array<float, 4>& value);

    private:
        bool m_isEnabled;
        unsigned int m_width;
        unsigned int m_height;

        std::vector<std::shared_ptr<Widget>> m_widgets;
    };
}
