#pragma once

#include <Buffer.h>
#include <string>
#include <glm/glm.hpp>
#include <Shader.h>
#include <glm/gtc/type_ptr.hpp>


class KroozOBJ
{
private:
  std::vector<float> vertices, normal;
  std::vector<unsigned int> indices;
  Buffer buffer;
  glm::mat4 ModelMatrix = glm::mat4(1.0f);
  GLuint shaderProgram;

  std::string names;

  glm::vec3 position = glm::vec3(0.0f);
  float rotation = 0.0f;
  float scale = 1.0f;

  void updateModelMatrix();

public:
  bool LoadOBJ(const std::string& filename);
  void Final();
  void setScale(float& value);
  void setRotation(float value);
  void setTranslation(glm::vec3 &value);
  glm::mat4 getModelMatrix();

  std::string FactorName(std::string name);

  void setShader(glm::vec3 data)
  {
      if (shaderProgram)
      {
          GLuint colorLocation = glGetUniformLocation(shaderProgram, "objectColor");
          if (colorLocation != -1)
          {
              glUseProgram(shaderProgram);
              glUniform3fv(colorLocation, 1, glm::value_ptr(data));
          }
          else
          {
              std::cerr << "Warning: Uniform 'objectColor' not found in shader!" << std::endl;
          }
      }
  }

  GLuint getShader()
  {
    return shaderProgram;
  }

  void setShaderProgram(GLuint program) { shaderProgram = program; }

  std::string GetName(){
    return this->names;
  }

};
