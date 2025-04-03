#pragma once

#include <Gl/glew.h>
#include <string>
#include <iostream>

class KroozShader
{
private:
  GLuint ShaderProgam;

public:
  void InitdefaultShader();
  void ShaderFromFile(std::string Vert, std::string Frag);
  GLuint getShaderProgram();

};
