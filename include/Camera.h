#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <unordered_map>

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::mat4 CameraMatrix;

    float Yaw = -90.0f;
    float Pitch = 0.0f;
    float MouseSensitivity = 0.08f;
    void UpdateVectors();

    Camera();
    static std::unordered_map<int, bool> KeyStates;

    void ProcessKeyboard(int key, int action);
    void UpdateCamera(float deltatime);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    glm::mat4 getCameraMatrix();

    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    void ProcessMouseMovement(float xOffset, float yOffset);

};

extern Camera* CurrentCamera;

