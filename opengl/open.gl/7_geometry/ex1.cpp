// https://open.gl/geometry

// g++ -std=c++17 -Wextra -Wall -Werror -pedantic ex1.cpp -lglfw -lGLEW
// -lGL -lSOIL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
  layout(line_strip, max_vertices = 16) out;

  in vec3 vColor[]; // Output from vertex shader for each vertex
  out vec3 fColor; // Output to fragment shader

  uniform mat4 model;
  uniform mat4 view;
  uniform mat4 proj;

  void main()
  {
    fColor = vColor[0]; // Point has only one vertex

    gl_Position = proj * view * model * gl_in[0].gl_Position;

    // +X direction is "North", -X direction is "South"
    // +Y direction is "Up",    -Y direction is "Down"
    // +Z direction is "East",  -Z direction is "West"
    //                                     N/S   U/D   E/W
    vec4 NEU = proj * view * model * vec4( 0.1,  0.1,  0.1, 0.0);
    vec4 NED = proj * view * model * vec4( 0.1, -0.1,  0.1, 0.0);
    vec4 NWU = proj * view * model * vec4( 0.1,  0.1, -0.1, 0.0);
    vec4 NWD = proj * view * model * vec4( 0.1, -0.1, -0.1, 0.0);
    vec4 SEU = proj * view * model * vec4(-0.1,  0.1,  0.1, 0.0);
    vec4 SED = proj * view * model * vec4(-0.1, -0.1,  0.1, 0.0);
    vec4 SWU = proj * view * model * vec4(-0.1,  0.1, -0.1, 0.0);
    vec4 SWD = proj * view * model * vec4(-0.1, -0.1, -0.1, 0.0);

    // Create a cube centered on the given point.
    gl_Position = gl_in[0].gl_Position + NED;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + NWD;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + SWD;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + SED;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + SEU;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + SWU;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + NWU;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + NEU;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + NED;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + SED;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + SEU;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + NEU;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + NWU;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + NWD;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + SWD;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + SWU;
    EmitVertex();

    EndPrimitive();
  }
)glsl";

// Fragment shader
const char* fragmentShaderSrc = R"glsl(
  #version 150 core

  in vec3 fColor;
  out vec4 outColor;

  void main()
  {
    outColor = vec4(fColor, 1.0);
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
  auto t_start = std::chrono::high_resolution_clock::now();

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

  GLfloat points[] = {
      //  Coordinates             Color
      -0.45f, 0.45f,  -0.45f, 1.0f, 0.0f, 0.0f,  //
      0.45f,  0.45f,  -0.45f, 0.0f, 1.0f, 0.0f,  //
      0.45f,  -0.45f, -0.45f, 0.0f, 0.0f, 1.0f,  //
      -0.45f, -0.45f, -0.45f, 1.0f, 1.0f, 0.0f,  //
      -0.45f, 0.45f,  0.45f,  0.0f, 1.0f, 1.0f,  //
      0.45f,  0.45f,  0.45f,  1.0f, 0.0f, 1.0f,  //
      0.45f,  -0.45f, 0.45f,  1.0f, 0.5f, 0.5f,  //
      -0.45f, -0.45f, 0.45f,  0.5f, 1.0f, 0.5f,  //
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
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        0);

  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        (void*)(3 * sizeof(GLfloat)));

  // Set up transformation matrices
  GLint uniModel = glGetUniformLocation(shaderProgram, "model");

  glm::mat4 view =
      glm::lookAt(glm::vec3(1.5f, 1.5f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 0.0f, 1.0f));
  GLint uniView = glGetUniformLocation(shaderProgram, "view");
  glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

  glm::mat4 proj =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
  GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Calculate transformation
    auto t_now = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(
                     t_now - t_start)
                     .count();

    glm::mat4 model;
    model = glm::rotate(model, 0.25f * time * glm::radians(180.0f),
                        glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    // Render frame
    glDrawArrays(GL_POINTS, 0, 8);
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
