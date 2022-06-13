//
// Created by Anatoliy on 02.06.2022.
//

#include "Rendering/GuiManager.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

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

//            ImGui::ShowDemoWindow();

            ImGui::Begin("Debug");
            for (const auto& w : m_widgets) {
                w->render();
            }
            ImGui::End();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }

    void GuiManager::colorPicker3(std::string label, std::array<float, 3>& value) {
        m_widgets.emplace_back(std::make_shared<ColorPicker3>(std::move(label), value));
    }

    void GuiManager::colorPicker4(std::string label, std::array<float, 4>& value) {
        m_widgets.emplace_back(std::make_shared<ColorPicker4>(std::move(label), value));
    }

    void GuiManager::inputNumber(std::string label, float& value, float& step) {
        m_widgets.emplace_back(std::make_shared<InputNumber>(std::move(label), value, step));
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
}
