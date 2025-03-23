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

  KroozOBJ AnimeAgain;
  AnimeAgain.LoadOBJ("Assets/anime.obj");
  AnimeAgain.setTranslation(glm::vec3(0.0f,0.0f,2.0f));
  AnimeAgain.setRotation(180.0f);

  KroozShader shader;
  shader.ShaderFromFile("Shaders/Vertex.glsl" , "Shaders/Fragment.glsl");

  KroozScene->AddObjects(std::make_unique<KroozOBJ>(CarModel));
  KroozScene->AddObjects(std::make_unique<KroozOBJ>(animeModel));
  KroozScene->AddObjects(std::make_unique<KroozOBJ>(AnimeAgain));


  KroozRenderer->MainLoop(shader.getShaderProgram(),KroozScene);

  return 0;
}
