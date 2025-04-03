#pragma once

#include <functional>
#include <vector>
#include <GLFW/glfw3.h>
#include "imgui.h"

class KroozInput
{
public:
    static std::vector<std::function<void(GLFWwindow*, int, int, int, int)>> callbacks;
    static std::vector<std::function<void(GLFWwindow*, double, double)>> Mousecallbacks;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        ImGuiIO& io = ImGui::GetIO();
        if (io.WantCaptureKeyboard)
            return;

        for (auto& callback : callbacks)
        {
            callback(window, key, scancode, action, mods);
        }
    }

    static void mouse_Callbacks(GLFWwindow* window, double xpos, double ypos)
    {

        for (auto& callback : Mousecallbacks)
        {
            callback(window, xpos, ypos);
        }
    }


    static void RegisterInputFunction(const std::function<void(GLFWwindow*, int, int, int, int)>& func)
    {
        callbacks.push_back(func);
    }

    static void RegisterMouseFunction(const std::function<void(GLFWwindow*, double, double)>& func)
    {
        Mousecallbacks.push_back(func);
    }

    static void AttachToWindow(GLFWwindow* window)
    {
        glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, mouse_Callbacks);
    }

};
