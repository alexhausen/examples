// https://open.gl/geometry

// g++ -std=c++17 -Wextra -Wall -Werror -pedantic 3_final.cpp -lglfw -lGLEW
// -lGL -lSOIL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex shader
const char* vertexShaderSrc = R"glsl(
  #version 150 core
  in vec2 pos;
  in vec3 color;
  in float sides;

  out vec3 vColor; // Output to geometry (or fragment) shader
  out float vSides;

  void main()
  {
    gl_Position = vec4(pos, 0.0, 1.0);
    vColor = color;
    vSides = sides;

  }
)glsl";

const char* geometryShaderSrc = R"glsl(
  #version 150 core

  layout(points) in;
  layout(line_strip, max_vertices = 64) out;

  in float vSides[];
  in vec3 vColor[]; // Output from vertex shader for each vertex
  out vec3 fColor; // Output to fragment shader

  const float PI = 3.1415926;

  void main()
  {
    fColor = vColor[0]; // Point has only one vertex

    for (int i = 0; i <= vSides[0]; i++) {
      // Angle between each side in radians
      float ang = PI * 2.0 / vSides[0] * i;

      // Offset from center of point (0.3 to accomodate for aspect ratio)
      vec4 offset = vec4(cos(ang) * 0.3, -sin(ang) * 0.4, 0.0, 0.0);
      gl_Position = gl_in[0].gl_Position + offset;

      EmitVertex();
    }
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
      // Coordinates  Color             Sides
      -0.45f, 0.45f,  1.0f, 0.0f, 0.0f, 4.0f,   //
      0.45f,  0.45f,  0.0f, 1.0f, 0.0f, 8.0f,   //
      0.45f,  -0.45f, 0.0f, 0.0f, 1.0f, 16.0f,  //
      -0.45f, -0.45f, 1.0f, 1.0f, 0.0f, 32.0f   //
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
