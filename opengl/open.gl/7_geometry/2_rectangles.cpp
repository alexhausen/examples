// https://open.gl/geometry

// g++ -std=c++17 -Wextra -Wall -Werror -pedantic 2_rectangles.cpp -lglfw -lGLEW
// -lGL -lSOIL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex shader
const char* vertexShaderSrc = R"glsl(
  #version 150 core
  in vec2 pos;
  in vec3 color;
  out vec3 vColor; // Output to geometry (or fragment) shader

  void main()
  {
    gl_Position = vec4(pos, 0.0, 1.0);
    vColor = color;
  }
)glsl";

const char* geometryShaderSrc = R"glsl(
  #version 150 core

  layout(points) in;
  layout(triangle_strip, max_vertices = 5) out;

  void main()
  {
    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.1, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.1, -0.1, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(-0.1, -0.1, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1, 0.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
  }
)glsl";

// Fragment shader
const char* fragmentShaderSrc = R"glsl(
  #version 150 core
  out vec4 outColor;

  void main()
  {
    outColor = vec4(1.0, 0.0, 0.0, 1.0);
  }
)glsl";

GLuint createShader(GLenum type, const GLchar* src) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);
  // verify if shader compiled correctly
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char buffer[512];
    glGetShaderInfoLog(shader, 512, nullptr, buffer);
    std::cout << "Compile shader error: " << buffer << std::endl;
  }
  return shader;
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  glewInit();

  // Compile and activate shaders
  GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSrc);
  GLuint geometryShader = createShader(GL_GEOMETRY_SHADER, geometryShaderSrc);
  GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, geometryShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  // Create Vertex Buffer Object with point coordinates
  GLuint vbo;
  glGenBuffers(1, &vbo);

  float points[] = {
      -0.45f, 0.45f,  1.0f, 0.0f, 0.0f,  // Red point
      0.45f,  0.45f,  0.0f, 1.0f, 0.0f,  // Green point
      0.45f,  -0.45f, 0.0f, 0.0f, 1.0f,  // Blue point
      -0.45f, -0.45f, 1.0f, 1.0f, 0.0f,  // Yellow point
  };
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  // Create Vertex Array Object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Specify layout of the vertex data
  GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(2 * sizeof(float)));

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render frame
    glDrawArrays(GL_POINTS, 0, 4);

    // swap buffers
    glfwSwapBuffers(window);
  }

  glDeleteProgram(shaderProgram);
  glDeleteShader(geometryShader);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  glfwTerminate();

  return 0;
}
