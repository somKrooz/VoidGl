#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Scene.h>
class Renderer{

private:
  GLFWwindow* MainWindow;
  glm::mat4 Projection = glm::mat4(1.0f);
  glm::mat4 View = glm::mat4(1.0f);

public:
  Renderer();
  void MainLoop(GLuint ShaderProgram , Scene* CurrentScene);
};
