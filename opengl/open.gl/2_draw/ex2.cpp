// Invert the colors of the triangle by altering the fragment shader.

// https://open.gl/drawing/

// g++ -std=c++17 -Wextra -Wall -Werror -pedantic ex2.cpp -lglfw -lGLEW -lGL -lm

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <cmath>
#include <cstdio>

// shader sources
const GLchar* vertexSource =
    "#version 150 core\n "
    "in vec2 position;"
    "in vec3 color;"
    "out vec3 Color;"
    "void main() {"
    "  Color = color;"
    "  gl_Position = vec4(position, 0.0, 1.0);"
    "}";

const GLchar* fragmentSource =
    "#version 150 core\n"
    "in vec3 Color;"
    "out vec4 outColor;"
    "void main() {"
    "  outColor = vec4(1.0 - Color, 1.0);"
    "}";

int main() {
  // setup for open GL (using GLFW to create window)
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  // portable way to access GL buffers
  glewExperimental = GL_TRUE;
  glewInit();

  // vertex array object (vao)
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // vertex buffer object (vbo)
  GLuint vbo;
  glGenBuffers(1, &vbo);  // Generate 1 buffer

  float vertices[] = {
      0.0f,  0.5f,  1.0f, 0.0f, 0.0f,  // Vertex 1: Red
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  // Vertex 2: Green
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f   // Vertex 3: Blue
  };

  // upload vertices
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // compile vertex shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, nullptr);
  glCompileShader(vertexShader);
  // verify if shader compiled correctly
  GLint status;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char buffer[512];
    glGetShaderInfoLog(vertexShader, 512, nullptr, buffer);
    return 1;
  }

  // compile fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
  glCompileShader(fragmentShader);
  // verify if shader compiled correctly
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char buffer[512];
    glGetShaderInfoLog(fragmentShader, 512, nullptr, buffer);
    return 1;
  }

  // combining shader into a program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  // glBindFragDataLocation(shaderProgram, 0, "outColor"); // - not needed now
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  // link vertex data and attributes
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
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

    // clear screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // swap buffers
    glfwSwapBuffers(window);
  }

  // tear down
  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glfwTerminate();

  return 0;
}
