#include <Renderer.h>
#include <Shader.h>
#include <Obj.h>

int main()
{
    Renderer* KroozRenderer = new Renderer();
    Scene* KroozScene = new Scene();

    KroozShader shader1;
    shader1.ShaderFromFile("Shaders/Vertex.glsl", "Shaders/Fragment.glsl");


    KroozShader shader3;
    shader3.ShaderFromFile("Shaders/Vertex.glsl", "Shaders/Fragment.glsl");

    KroozOBJ carModel;
    carModel.LoadOBJ("Assets/Car.obj");
    carModel.setShaderProgram(shader1.getShaderProgram());
    carModel.setShader(glm::vec3(1.0f,1.0f,1.0f));


    KroozOBJ anime;
    anime.LoadOBJ("Assets/anime.obj");
    anime.setTranslation(glm::vec3(0.0f, 0.0f, 2.0f));
    anime.setRotation(180.0f);
    anime.setShaderProgram(shader3.getShaderProgram());
    anime.setShader(glm::vec3(1.0f,1.0f,1.0f));

    KroozScene->AddObjects(std::make_unique<KroozOBJ>(carModel));
    KroozScene->AddObjects(std::make_unique<KroozOBJ>(anime));

    KroozRenderer->MainLoop(KroozScene);

    return 0;
}
