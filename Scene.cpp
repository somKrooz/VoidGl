#include <Scene.h>
#include<glm/gtc/type_ptr.hpp>


Scene::Scene()
{
  this->index = 0;
}

void Scene::AddObjects(std::unique_ptr<KroozOBJ> obj)
{
  if(obj != nullptr)
  {
    Objects.push_back(std::move(obj));
  }
}

bool Scene::RenderEveryThing(GLuint defaultMatrixLocation)
{
    if(Objects.size() > 0)
    {
        for(auto &obj : Objects)
        {

            GLuint currentProgram = obj->getShader();
            glUseProgram(currentProgram);


            GLuint matrixLocation = glGetUniformLocation(currentProgram, "model");
            glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(obj->getModelMatrix()));
            obj->Final();
        }
        return true;
    }
    else
    {
        return false;
    }
}
