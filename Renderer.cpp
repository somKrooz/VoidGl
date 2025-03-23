#include <Renderer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include  <Camera.h>


Renderer::Renderer()
{
  if (glfwInit() != GLFW_TRUE) {
    return;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  MainWindow = glfwCreateWindow(1280, 720, "KroozEngine", NULL, NULL);
  if (!MainWindow) {
      glfwTerminate();
      return;
  }

  glfwMakeContextCurrent(MainWindow);
  if (glewInit() != GLEW_OK) {
    return;
  }

  glEnable(GL_DEPTH_TEST);
  Projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);

  CurrentCamera = &cam;
  glfwSetWindowAttrib(MainWindow ,  GLFW_RESIZABLE, GL_FALSE);
}

void Renderer::MainLoop(GLuint ShaderProgram ,Scene* CurrentScene )
{
  //Later Remove
  glm::vec3 lightPos(3.0f, 5.0f, 2.0f);
  glm::vec3 viewPos(0.0f, 0.0f, 0.0f);

  float before = static_cast<float>(glfwGetTime());

  while (!glfwWindowShouldClose(MainWindow))
  {
    glfwSetKeyCallback(MainWindow, Camera::KeyCallback);
    glfwSetCursorPosCallback(MainWindow, Camera::MouseCallback);
    glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(cam.getCameraMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));

    float Current = static_cast<float>(glfwGetTime());
    float deltatime = Current - before;
    before = Current;

    cam.UpdateCamera(deltatime);
    //Later Remove
    glUniform3fv(glGetUniformLocation(ShaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(ShaderProgram, "viewPos"), 1, glm::value_ptr(viewPos));
    glUniform3f(glGetUniformLocation(ShaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(ShaderProgram, "objectColor"), 1.0f, 1.0f, 1.0f);


    glViewport(0, 0, 1280, 720);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(ShaderProgram);
    CurrentScene->RenderEveryThing(glGetUniformLocation(ShaderProgram, "model"));

    glfwSwapBuffers(MainWindow);
    glfwPollEvents();
  }

  glfwDestroyWindow(MainWindow);
  glfwTerminate();

  glDeleteShader(ShaderProgram);
  delete CurrentScene;
}
