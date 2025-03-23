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
