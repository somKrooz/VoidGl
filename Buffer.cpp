#include <Buffer.h>


Buffer::Buffer()
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
}

void Buffer::Bind()
{
  glBindVertexArray(VAO);
}

void Buffer::UnBind()
{
  glBindVertexArray(0);
}

void Buffer::SetupData(const std::vector<float>& vertices,const std::vector<float>& normals,
  GLenum usage)
{

  std::vector<float> MainData;
  size_t vertexCount = vertices.size() / 3;
  size_t normalCount = normals.size() / 3;

  bool hasNormals = (normalCount == vertexCount);
  for (size_t i = 0; i < vertexCount; i++) {
    MainData.push_back(vertices[i * 3 + 0]);
    MainData.push_back(vertices[i * 3 + 1]);
    MainData.push_back(vertices[i * 3 + 2]);

    if (hasNormals) {
      MainData.push_back(normals[i * 3 + 0]);
      MainData.push_back(normals[i * 3 + 1]);
      MainData.push_back(normals[i * 3 + 2]);
    }
  }

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, MainData.size() * sizeof(float), MainData.data(), usage);

  // Position (location 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Normal (location 1)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

}

void Buffer::SetupIndices(const std::vector<unsigned int>& indices)
{
  indexCount = indices.size();
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
  glBindVertexArray(0);
  hasEBO = true;
}


void Buffer::Draw(GLenum mode)
{
  glBindVertexArray(VAO);
  if (hasEBO)
    glDrawElements(mode, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, 0);
  else
    glDrawArrays(mode, 0, static_cast<GLsizei>(indexCount));
    glBindVertexArray(0);
}

Buffer::~Buffer()
{
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
}
