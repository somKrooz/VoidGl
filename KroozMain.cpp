#include <Renderer.h>
#include <Shader.h>
#include <Obj.h>

int main()
{
  Renderer* KroozRenderer = new Renderer();
  Scene* KroozScene = new Scene();

  KroozOBJ animeModel;
  animeModel.LoadOBJ("Assets/anime.obj");

  KroozOBJ CarModel;
  CarModel.LoadOBJ("Assets/Car.obj");

  KroozShader shader;
  shader.ShaderFromFile("Shaders/Vertex.glsl" , "Shaders/Fragment.glsl");

  KroozScene->AddObjects(std::make_unique<KroozOBJ>(CarModel));
  KroozScene->AddObjects(std::make_unique<KroozOBJ>(animeModel));
  KroozRenderer->MainLoop(shader.getShaderProgram(),KroozScene);

  return 0;
}
