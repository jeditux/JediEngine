//
// Created by Anatoliy on 02.06.2022.
//

#include "Rendering/GuiManager.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <stdexcept>

namespace Rendering {

    GuiManager::GuiManager(GLFWwindow* window, unsigned int width, unsigned int height) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        m_width = width;
        m_height = height;
        m_isEnabled = false;
    }

    bool GuiManager::isEnabled() const {
        return m_isEnabled;
    }

    void GuiManager::setEnabled(bool value) {
        m_isEnabled = value;
    }

    void GuiManager::render() {
        if (m_isEnabled) {
            ImGuiIO &io = ImGui::GetIO();
            io.DisplaySize.x = m_width;
            io.DisplaySize.y = m_height;

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::ShowDemoWindow();

            for (const auto& w : m_widgets) {
                w->render();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }

    GuiManager &GuiManager::addWidget(const std::shared_ptr<Widget>& childWidget) {
        m_widgets.emplace_back(childWidget);
        return *this;
    }

    Window::Window(std::string label, size_t xPos, size_t yPos, size_t width, size_t height)
        : m_label(std::move(label)), m_xPos(xPos), m_yPos(yPos), m_width(width), m_height(height) {
    }

    void Window::render() {
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + m_xPos, main_viewport->WorkPos.y + m_yPos));
        ImGui::SetNextWindowSize(ImVec2(m_width, m_height), ImGuiCond_FirstUseEver);
        ImGui::Begin(m_label.c_str());
        for (const auto& w : m_widgets) {
            w->render();
        }
        ImGui::End();
    }

    Widget& Widget::addChildWidget(const std::shared_ptr<Widget>& childWidget) {
        throw std::runtime_error("Unsupported operation");
    }

    Widget& Window::addChildWidget(const std::shared_ptr<Widget>& childWidget) {
        m_widgets.emplace_back(childWidget);
        return *this;
    }

    ColorPicker3::ColorPicker3(std::string label, std::array<float, 3> &value)
            : m_label(std::move(label)), m_value(value) {
    }

    void ColorPicker3::render() {
        ImGui::ColorPicker3(m_label.c_str(), m_value.data());
    }

    ColorPicker4::ColorPicker4(std::string label, std::array<float, 4> &value)
        : m_label(std::move(label)), m_value(value) {
    }

    void ColorPicker4::render() {
        ImGui::ColorPicker4(m_label.c_str(), m_value.data());
    }

    InputNumber::InputNumber(std::string label, float& value, float& step)
        : m_label(std::move(label)), m_value(value), m_step(step) {
    }

    void InputNumber::render() {
        ImGui::InputScalar(m_label.c_str(), ImGuiDataType_Float, &m_value, &m_step);
    }

    RadioButton::RadioButton(std::string label, int &var, int value)
        : m_label(std::move(label)), m_var(var), m_value(value) {
    }

    void RadioButton::render() {
        ImGui::RadioButton(m_label.c_str(), &m_var, m_value);
    }

    Text::Text(std::string value) : m_value(std::move(value)) {
    }

    void Text::render() {
        ImGui::Text(m_value.c_str());
    }

    std::shared_ptr<Window> WidgetFactory::window(std::string label, size_t xPos, size_t yPos, size_t width, size_t height) {
        return std::make_shared<Window>(std::move(label), xPos, yPos, width, height);
    }

    std::shared_ptr<ColorPicker4> WidgetFactory::colorPicker4(std::string label, std::array<float, 4>& value) {
        return std::make_shared<ColorPicker4>(std::move(label), value);
    }

    std::shared_ptr<ColorPicker3> WidgetFactory::colorPicker3(std::string label, std::array<float, 3>& value) {
        return std::make_shared<ColorPicker3>(std::move(label), value);
    }

    std::shared_ptr<InputNumber> WidgetFactory::inputNumber(std::string label, float& value, float& step) {
        return std::make_shared<InputNumber>(std::move(label), value, step);
    }

    std::shared_ptr<RadioButton> WidgetFactory::radioButton(std::string label, int& var, int value) {
        return std::make_shared<RadioButton>(std::move(label), var, value);
    }

    std::shared_ptr<Text> WidgetFactory::text(std::string value) {
        return std::make_shared<Text>(std::move(value));
    }
}
