#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Scene.h>
#include <Camera.h>

class Renderer{

private:
  GLFWwindow* MainWindow;
  glm::mat4 Projection = glm::mat4(1.0f);
  glm::mat4 View = glm::mat4(1.0f);
  Camera cam;
public:
  Renderer();
  void MainLoop( Scene* CurrentScene);
};
