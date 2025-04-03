#include <Renderer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Camera.h>
#include <Input.hh>

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

std::vector<std::function<void(GLFWwindow*, int, int, int, int)>> KroozInput::callbacks;
std::vector<std::function<void(GLFWwindow*, double, double)>> KroozInput::Mousecallbacks;

int index = 0;

void SetDarkStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Set colors based on Unreal Engine's dark theme
    colors[ImGuiCol_WindowBg]           = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg]             = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_PopupBg]             = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);

    colors[ImGuiCol_Border]              = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
    colors[ImGuiCol_BorderShadow]        = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    colors[ImGuiCol_FrameBg]             = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]      = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_FrameBgActive]       = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);

    colors[ImGuiCol_TitleBg]             = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBgActive]       = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    // colors[ImGuiCol_TitleBgCollapsed]    = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

    // colors[ImGuiCol_Button]              = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    // colors[ImGuiCol_ButtonHovered]       = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    // colors[ImGuiCol_ButtonActive]        = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);

    colors[ImGuiCol_Header]              = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    // colors[ImGuiCol_HeaderHovered]       = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    // colors[ImGuiCol_HeaderActive]        = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);

    // colors[ImGuiCol_Separator]           = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
    // colors[ImGuiCol_SeparatorHovered]    = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    // colors[ImGuiCol_SeparatorActive]     = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);

    colors[ImGuiCol_ScrollbarBg]         = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    // colors[ImGuiCol_ScrollbarGrab]       = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    // colors[ImGuiCol_ScrollbarGrabHovered]= ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    // colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);

    // Rounding and border thickness
    style.WindowRounding    = 3.0f;
    // style.FrameRounding     = 3.0f;
    // style.PopupRounding     = 3.0f;
    // style.GrabRounding      = 3.0f;
    // style.ScrollbarRounding = 3.0f;

    // style.WindowBorderSize  = 1.0f;
    style.FrameBorderSize   = 1.0f;
    // style.PopupBorderSize   = 1.0f;
}


Renderer::Renderer()
{
    if (glfwInit() != GLFW_TRUE) {
        return;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    SetDarkStyle();
    ImGui_ImplGlfw_InitForOpenGL(MainWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    CurrentCamera = &cam;
}

void Renderer::MainLoop(Scene* CurrentScene)
{
  glm::vec3 lightPos(2.5f, 6.0f, 4.0f);
  glm::vec3 viewPos(0.0f, 1.5f, 5.0f);

  glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  float before = static_cast<float>(glfwGetTime());

  glm::vec3 Color;

  float scale = 1.0f;
  float Rotate = 0.0f;
  static glm::vec3 translation = glm::vec3(0.0f);
  glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  double xpos;
  double ypos;

  while (!glfwWindowShouldClose(MainWindow))
  {
    glfwPollEvents();
    glfwGetCursorPos(MainWindow , &xpos, &ypos);

    float Current = static_cast<float>(glfwGetTime());
    float deltaTime = Current - before;
    before = Current;

    glViewport(0, 0, 1280, 720);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(.2f,.2f,.2f,1.0f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Object List", nullptr, ImGuiWindowFlags_NoCollapse );
    for (int i = 0; i < CurrentScene->GetObjects().size(); i++) {
        std::string buttonLabel = CurrentScene->GetObjects()[i]->GetName();

        if (ImGui::Button(buttonLabel.c_str())) {
            index = i;
        }
    }
    ImGui::End();

    ImGui::Begin("Inspector", nullptr);
    ImGui::Text("Transformation");

    if (ImGui::SliderFloat("Scale", &scale, 0.1f, 2.0f)) {
        CurrentScene->GetObjects()[index]->setScale(scale);
    }

    if (ImGui::SliderFloat("Rotate", &Rotate, 0.0f, 360.0f)) {
        CurrentScene->GetObjects()[index]->setRotation(Rotate);
    }

    if (ImGui::DragFloat3("Position", glm::value_ptr(translation), 0.1f, -10.0f, 10.0f)) {
        CurrentScene->GetObjects()[index]->setTranslation(translation);
    }

    ImGui::Text("Color Picker");
    if (ImGui::ColorPicker3("Color", glm::value_ptr(Color), ImGuiColorEditFlags_PickerHueWheel)) {
        CurrentScene->GetObjects()[index]->setShader(Color);
    }
    ImGui::End();

    glfwSetKeyCallback(MainWindow,KroozInput::key_callback);
    glfwSetCursorPosCallback(MainWindow,KroozInput::mouse_Callbacks);

    ImGui_ImplGlfw_CursorPosCallback(MainWindow, xpos, ypos);
    cam.UpdateCamera(deltaTime);

    for (auto& obj : CurrentScene->GetObjects()) {
      GLuint program = obj->getShader();
      glUseProgram(program);

      glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE,
                          glm::value_ptr(cam.getCameraMatrix()));
      glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE,
                          glm::value_ptr(Projection));

      glUniform3fv(glGetUniformLocation(program, "lightPos"), 1, glm::value_ptr(lightPos));
      glUniform3fv(glGetUniformLocation(program, "viewPos"), 1, glm::value_ptr(viewPos));
      glUniform3f(glGetUniformLocation(program, "lightColor"), 1.0f, 1.0f, 1.0f);
    }

    CurrentScene->RenderEveryThing(0);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(MainWindow);

  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(MainWindow);
  glfwTerminate();
  delete CurrentScene;
}
