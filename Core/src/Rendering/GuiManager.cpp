//
// Created by Anatoliy on 02.06.2022.
//

#include "Rendering/GuiManager.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

namespace Rendering {

    void GuiManager::init(GLFWwindow* window, unsigned int width, unsigned int height) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        m_width = width;
        m_height = height;
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

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }
}
