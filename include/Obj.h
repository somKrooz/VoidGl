#pragma once

#include <Buffer.h>
#include <string>
//GLM
#include <glm/glm.hpp>

class KroozOBJ
{
private:
  std::vector<float> vertices, normal;
  std::vector<unsigned int> indices;
  Buffer buffer;
  glm::mat4 ModelMatrix = glm::mat4(1.0f);

public:
  bool LoadOBJ(const std::string& filename);
  void Final();
  void setScale(float& value);
  void setRotation(float value);
  void setTranslation(glm::vec3 &value);

  glm::mat4 getModelMatrix();
};
