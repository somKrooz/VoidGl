#pragma once

#include <GL/glew.h>
#include <vector>

class Buffer{

private:
    unsigned int VBO, VAO, EBO;
    bool hasEBO = false;
    size_t indexCount = 0;

public:
  Buffer();
  void Bind();
  void UnBind();
  void SetupData(const std::vector<float>& vertices,const std::vector<float>& normals,
    GLenum usage = GL_STATIC_DRAW);

  void SetupIndices(const std::vector<unsigned int>& indices);
  void Draw(GLenum mode = GL_TRIANGLES);
  ~Buffer();
};
