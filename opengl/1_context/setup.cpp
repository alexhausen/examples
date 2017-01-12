// https://open.gl/context/

// g++ -std=c++17 -Wextra -Wall -Werror -pedantic setup.cpp -lglfw -lGLEW

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

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
  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  printf("%u\n", vertexBuffer);

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
  }

  glfwTerminate();
}
