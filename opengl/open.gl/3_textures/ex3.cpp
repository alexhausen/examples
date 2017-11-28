// Now try adding distortion with sin and the time variable to simulate water
// expected result: https://open.gl/media/img/c3_window3.png

// https://open.gl/textures/

// g++ -std=c++17 -Wextra -Wall -Werror -pedantic ex3.cpp -lglfw -lGLEW -lGL
// -lSOIL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <chrono>
#include <cstdio>

// shader sources, in GLSL (OpenGL Shading Language)
const GLchar* vertexSource =
    "#version 150 core\n "
    "in vec2 position;"
    "in vec2 texcoord;"
    "out vec2 Texcoord;"
    "void main() {"
    "  Texcoord = texcoord;"
    "  gl_Position = vec4(position, 0.0, 1.0);"
    "}";

const GLchar* fragmentSource =
    "#version 150 core\n"
    "in vec2 Texcoord;"
    "out vec4 outColor;"
    "uniform sampler2D tex;"
    "uniform float time;"
    "void main() {"
    "  if (Texcoord.y < 0.5)"
    "    outColor = texture(tex, Texcoord);"
    "  else"
    "    outColor = texture(tex,"
    "        vec2(Texcoord.x + sin(Texcoord.y * 60 + time) / 30.0, 1.0 - "
    "Texcoord.y)) * vec4(0.7, 0.7, 1.0, 1.0);"
    "}";

int main() {
  // setup for open GL (using GLFW to create window)
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  // portable way to access GL buffers
  glewExperimental = GL_TRUE;
  glewInit();

  // GL version
  printf("OpenGL version: %s. GLSL version: %s.\n", glGetString(GL_VERSION),
         glGetString(GL_SHADING_LANGUAGE_VERSION));

  // vertex array object (vao)
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object and copy the vertex data to it
  GLuint vbo;
  glGenBuffers(1, &vbo);  // Generate 1 buffer

  float vertices[] = {
      //  Position  Texcoords
      -0.5f, 0.5f,  0.0f, 0.0f,  // Top-left
      0.5f,  0.5f,  1.0f, 0.0f,  // Top-right
      0.5f,  -0.5f, 1.0f, 1.0f,  // Bottom-right
      -0.5f, -0.5f, 0.0f, 1.0f   // Bottom-left
  };
  // upload vertices
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Create an element array
  GLuint ebo;
  glGenBuffers(1, &ebo);

  GLuint elements[] = {0, 1, 2, 2, 3, 0};
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
               GL_STATIC_DRAW);

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
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

  GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                        (void*)(2 * sizeof(float)));

  // Load texture
  GLuint tex;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);

  int width, height;
  unsigned char* image =
      SOIL_load_image("../png/sample.png", &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // uniform triangleColor from fragmentShader
  GLint uniTime = glGetUniformLocation(shaderProgram, "time");
  glUniform1f(uniTime, 0.0f);

  auto t_start = std::chrono::high_resolution_clock::now();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    // clear screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the time uniform
    auto t_now = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(
                     t_now - t_start)
                     .count();
    glUniform1f(uniTime, time);

    // Draw a rectangle from the 2 triangles using 6 indices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // swap buffers
    glfwSwapBuffers(window);
  }

  // tear down

  glDeleteTextures(1, &tex);
  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glfwTerminate();

  return 0;
}
