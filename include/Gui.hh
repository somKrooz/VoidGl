#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

class GUI
{
private:
    GLFWwindow* window;

public:
    GUI(GLFWwindow* window)
    {
        this->window = window;
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;

        // Set ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        // This is critical - it installs callbacks that ImGui needs
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void Start()
    {
        // Start a new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create a test window
        ImGui::Begin("Krooz Engine Debug");
        ImGui::Text("Hello, Krooz!");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

        // Add a button to test interaction
        if (ImGui::Button("Test Button")) {
            // This would execute when the button is clicked
        }

        ImGui::End();

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    ~GUI()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
};
