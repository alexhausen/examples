// https://open.gl/context/

// create a window context with glfw
// g++ -std=c++17 -Wextra -Wall -Werror -pedantic glfw.cpp -lglfw -lGLEW -lGL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>

void shutDown(int debug) {
  GLenum errCode = glGetError();
  const GLubyte* errMsg = glewGetErrorString(errCode);
  printf("%d - error %d, '%s'\n", debug, errCode, errMsg);
  glfwTerminate();
  exit(1);
}

int main() {
  // create window context using GLFW
  if (glfwInit() != GL_TRUE) shutDown(1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
  if (window == nullptr) shutDown(2);
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
