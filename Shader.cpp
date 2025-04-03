#include <Default.hh>
#include <Shader.h>

#include <fstream>
#include <sstream>

void KroozShader::InitdefaultShader()
{
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);


  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  ShaderProgam = glCreateProgram();
  glAttachShader(ShaderProgam, vertexShader);
  glAttachShader(ShaderProgam, fragmentShader);
  glLinkProgram(ShaderProgam);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

}

GLuint KroozShader::getShaderProgram()
{
  return ShaderProgam;
}


void KroozShader::ShaderFromFile(std::string Vert, std::string Frag)
{
    // Read Vertex Shader
    std::ifstream vertFile(Vert);
    std::stringstream vertBuffer;
    vertBuffer << vertFile.rdbuf();
    std::string vertexShaderCode = vertBuffer.str();

    // Read Fragment Shader
    std::ifstream fragFile(Frag);
    std::stringstream fragBuffer;
    fragBuffer << fragFile.rdbuf();
    std::string fragmentShaderCode = fragBuffer.str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);


    // Compile Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);


    // Link Shaders into Program
    ShaderProgam = glCreateProgram();
    glAttachShader(ShaderProgam, vertexShader);
    glAttachShader(ShaderProgam, fragmentShader);
    glLinkProgram(ShaderProgam);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
