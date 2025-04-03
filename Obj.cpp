#include <Obj.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <iostream>
#include <filesystem>
#include <glm/gtc/matrix_transform.hpp>


bool KroozOBJ::LoadOBJ(const std::string &path)
{
  std::string FinalName = FactorName(path);
  this->names = FinalName;

  tinyobj::attrib_t attrb;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> mat;
  std::string warn, err;

  vertices.clear();
  normal.clear();
  indices.clear();


  if(!tinyobj::LoadObj(&attrb , &shapes , &mat, &err, path.c_str())){
    return false;
  }

  for (const auto& shape : shapes)
  {
    for (const auto& index : shape.mesh.indices)
    {
      indices.push_back(static_cast<unsigned int>(indices.size()));

      if(index.vertex_index >= 0)
      vertices.push_back(attrb.vertices[3 * index.vertex_index + 0]);
      vertices.push_back(attrb.vertices[3 * index.vertex_index + 1]);
      vertices.push_back(attrb.vertices[3 * index.vertex_index + 2]);

      if(index.normal_index >= 0)
      {
        normal.push_back(attrb.normals[3 * index.normal_index + 0]);
        normal.push_back(attrb.normals[3 * index.normal_index + 1]);
        normal.push_back(attrb.normals[3 * index.normal_index + 2]);
      }
    }
  }

  std::cout<<"Total Indiced: " << indices.size() << std::endl;
  std::cout<<"Total Vertices: " << vertices.size() << std::endl;

  buffer.SetupData(vertices,normal);
  buffer.SetupIndices(indices);

  return true;
}

void KroozOBJ::Final()
{
  buffer.Draw();
}


void KroozOBJ::setTranslation( glm::vec3& value) {
  position = value;
  updateModelMatrix();
}

void KroozOBJ::setRotation(float value) {
  rotation = value;
  updateModelMatrix();
}

void KroozOBJ::setScale(float &value) {
  scale = value;
  updateModelMatrix();
}

void KroozOBJ::updateModelMatrix() {

    this->ModelMatrix = glm::mat4(1.0f);

    this->ModelMatrix = glm::translate(ModelMatrix, position);
    this->ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    this->ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scale));

}


glm::mat4 KroozOBJ::getModelMatrix()
{
  return ModelMatrix;
}

std::string KroozOBJ::FactorName(std::string name)
{
  std::filesystem::path filePath(name);
  std::string fileName = filePath.filename().string();
  return fileName;
}
