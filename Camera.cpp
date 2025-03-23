#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera* CurrentCamera = nullptr;
std::unordered_map<int, bool> Camera::KeyStates;

Camera::Camera()
{
    Position = glm::vec3(0.0f, 0.0f, 10.0f);
    Up = glm::vec3(0.0f, 1.0f, 0.0f);
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    Right = glm::normalize(glm::cross(Front, Up));

    CameraMatrix = glm::lookAt(Position, Position + Front, Up);
}

void Camera::UpdateCamera(float dt)
{
  float velocity = 5.0f * dt;

  if (KeyStates[GLFW_KEY_W]) Position += velocity * Front;
  if (KeyStates[GLFW_KEY_S]) Position -= velocity * Front;
  if (KeyStates[GLFW_KEY_A]) Position -= velocity * Right;
  if (KeyStates[GLFW_KEY_D]) Position += velocity * Right;
  if (KeyStates[GLFW_KEY_Q]) Position += velocity * Up;
  if (KeyStates[GLFW_KEY_E]) Position -= velocity * Up;

  CameraMatrix = glm::lookAt(Position, Position + Front, Up);
}


void Camera::ProcessKeyboard(int key, int action)
{
  if (action == GLFW_PRESS) KeyStates[key] = true;
  if (action == GLFW_RELEASE) KeyStates[key] = false;

}


void Camera::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (CurrentCamera)
        CurrentCamera->ProcessKeyboard(key, action);
}

glm::mat4 Camera::getCameraMatrix()
{
    return CameraMatrix;
}


//Mouse Thing
void Camera::ProcessMouseMovement(float xOffset, float yOffset)
{
    xOffset *= MouseSensitivity;
    yOffset *= MouseSensitivity;

    Yaw += xOffset;
    Pitch += yOffset;

    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    UpdateVectors();
}


void Camera::UpdateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, glm::vec3(0.0f, 1.0f, 0.0f)));
    Up = glm::normalize(glm::cross(Right, Front));

    CameraMatrix = glm::lookAt(Position, Position + Front, Up);
}

void Camera::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse = true;
    static float lastX = 400, lastY = 300;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    if (CurrentCamera)
        CurrentCamera->ProcessMouseMovement(xOffset, yOffset);
}
