static inline const char* vertexShaderSource = R"(
  #version 330 core
  layout(location = 0) in vec3 aPos;

  uniform mat4 Projection;
  uniform mat4 view;

  void main()
  {
      gl_Position = Projection * view * vec4(aPos, 1.0);
  }
)";

static inline const char* fragmentShaderSource = R"(
  #version 330 core
  out vec4 FragColor;

  void main()
  {
      FragColor = vec4(1.0, 0.5, 0.2, 1.0);
  }
)";
