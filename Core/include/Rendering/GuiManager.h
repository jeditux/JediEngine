//
// Created by Anatoliy on 02.06.2022.
//

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <array>

struct GLFWwindow;

namespace Rendering {

    class Widget {
    public:
        virtual void render() = 0;
        virtual Widget& addChildWidget(const std::shared_ptr<Widget>& childWidget);
    };

    class Window : public Widget {
    public:
        Window(std::string label, size_t xPos, size_t yPos, size_t width, size_t height);
        void render() override;
        Widget& addChildWidget(const std::shared_ptr<Widget>& childWidget) override;
    private:
        std::string m_label;
        size_t m_xPos;
        size_t m_yPos;
        size_t m_width;
        size_t m_height;
        std::vector<std::shared_ptr<Widget>> m_widgets;
    };

    class HorizontalLayout : public Widget {
    public:
        void render() override;
        Widget& addChildWidget(const std::shared_ptr<Widget>& childWidget) override;
    private:
        std::vector<std::shared_ptr<Widget>> m_widgets;
    };

    class ColorPicker4 : public Widget {
    public:
        ColorPicker4(std::string label, std::array<float, 4>& value);
        void render() override;
    private:
        std::string m_label;
        std::array<float, 4>& m_value;
    };

    class ColorPicker3 : public Widget {
    public:
        ColorPicker3(std::string label, std::array<float, 3>& value);
        void render() override;
    private:
        std::string m_label;
        std::array<float, 3>& m_value;
    };

    class ColorEdit4 : public Widget {
    public:
        ColorEdit4(std::string label, std::array<float, 4>& value);
        void render() override;
    private:
        std::string m_label;
        std::array<float, 4>& m_value;
    };

    class ColorEdit3 : public Widget {
    public:
        ColorEdit3(std::string label, std::array<float, 3>& value);
        void render() override;
    private:
        std::string m_label;
        std::array<float, 3>& m_value;
    };

    class InputNumber : public Widget {
    public:
        InputNumber(std::string label, float& value, float& step);
        void render() override;
    private:
        std::string m_label;
        float& m_value;
        float& m_step;
    };

    class RadioButton : public Widget {
    public:
        RadioButton(std::string label, int& var, int value);
        void render() override;
    private:
        std::string m_label;
        int& m_var;
        int m_value;
    };

    class Slider : public Widget {
    public:
        Slider(std::string label, float& value, float min, float max);
        void render() override;
    private:
        std::string m_label;
        float& m_value;
        float m_min;
        float m_max;
    };

    class Text : public Widget {
    public:
        Text(std::string value);
        void render() override;
    private:
        std::string m_value;
    };

    class Spacing : public Widget {
    public:
        void render() override;
    };

    class WidgetFactory {
    public:
        static std::shared_ptr<Window> window(std::string label, size_t xPos, size_t yPos, size_t width, size_t height);
        static std::shared_ptr<HorizontalLayout> horizontalLayout();
        static std::shared_ptr<ColorPicker4> colorPicker4(std::string label, std::array<float, 4>& value);
        static std::shared_ptr<ColorPicker3> colorPicker3(std::string label, std::array<float, 3>& value);
        static std::shared_ptr<ColorEdit4> colorEdit4(std::string label, std::array<float, 4>& value);
        static std::shared_ptr<ColorEdit3> colorEdit3(std::string label, std::array<float, 3>& value);
        static std::shared_ptr<InputNumber> inputNumber(std::string label, float& value, float& step);
        static std::shared_ptr<RadioButton> radioButton(std::string label, int& var, int value);
        static std::shared_ptr<Slider> slider(std::string label, float& value, float min, float max);
        static std::shared_ptr<Text> text(std::string value);
        static std::shared_ptr<Spacing> spacing();
    };

    class GuiManager {
    public:
        GuiManager(GLFWwindow* window, unsigned int width, unsigned int height);

        GuiManager(const GuiManager&) = delete;
        GuiManager& operator=(const GuiManager&) = delete;

        bool isEnabled() const;
        void setEnabled(bool value);
        void render();

        GuiManager& addWidget(const std::shared_ptr<Widget>& childWidget);

    private:
        bool m_isEnabled;
        unsigned int m_width;
        unsigned int m_height;

        std::vector<std::shared_ptr<Widget>> m_widgets;
    };
}
