// https://open.gl/framebuffers

// Try adding a panel in the 3D scene displaying that very scene from a
// different angle

// g++ -std=c++17 -Wextra -Wall -Werror -pedantic ex2.cpp -lglfw -lGLEW
// -lGL -lSOIL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>
#include <cstdio>

// Shader sources
const GLchar* sceneVertexSource = R"glsl(
    #version 150 core
    in vec3 position;
    in vec3 color;
    in vec2 texcoord;
    out vec3 Color;
    out vec2 Texcoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;
    uniform vec3 overrideColor;
    void main()
    {
        Color = color * overrideColor;
        Texcoord = texcoord;
        gl_Position = proj * view * model * vec4(position, 1.0);
    }
)glsl";

const GLchar* sceneFragmentSource = R"glsl(
    #version 150 core
    in vec3 Color;
    in vec2 Texcoord;
    out vec4 outColor;
    uniform sampler2D texKitten;
    uniform sampler2D texPuppy;
    void main()
    {
        vec4 texColor = mix(texture(texKitten, Texcoord), texture(texPuppy, Texcoord), 0.5);
        outColor = vec4(Color, 1.0) * texColor;
    }
)glsl";

const GLchar* panelVertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    in vec2 texcoord;
    out vec2 Texcoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;
    void main()
    {
        Texcoord = texcoord;
        gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
    }
)glsl";
const GLchar* panelFragmentSource = R"glsl(
    #version 150 core
    in vec2 Texcoord;
    out vec4 outColor;
    uniform sampler2D texFramebuffer;
    void main()
    {
        outColor = texture(texFramebuffer, Texcoord);
    }
)glsl";

// Cube vertices
GLfloat cubeVertices[] = {
    // X     Y     Z     R      G      B      U     V
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  //
    0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  //
    -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  //
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  //

    -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  //
    0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  //
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  //
    -0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  //
    -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  //

    -0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //
    -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  //
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  //
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  //
    -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  //
    -0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //

    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  //
    0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  //
    0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  //
    0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  //
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  //
    0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  //
    0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //
    0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //
    -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  //
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  //

    -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  //
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //
    -0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  //
    -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  //

    -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //
    1.0f,  -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //
    1.0f,  1.0f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,  //
    1.0f,  1.0f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,  //
    -1.0f, 1.0f,  -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  //
    -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f   //
};

// Quad vertices
GLfloat quadVertices[] = {
    -1.0f, 1.0f,  0.0f, 1.0f,  //
    1.0f,  1.0f,  1.0f, 1.0f,  //
    1.0f,  -1.0f, 1.0f, 0.0f,  //

    1.0f,  -1.0f, 1.0f, 0.0f,  //
    -1.0f, -1.0f, 0.0f, 0.0f,  //
    -1.0f, 1.0f,  0.0f, 1.0f   //
};

// Create a texture from an image file
GLuint loadTexture(const GLchar* path) {
  GLuint texture;
  glGenTextures(1, &texture);

  int width, height;
  unsigned char* image;

  glBindTexture(GL_TEXTURE_2D, texture);
  image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return texture;
}

void createShaderProgram(const GLchar* vertSrc, const GLchar* fragSrc,
                         GLuint& vertexShader, GLuint& fragmentShader,
                         GLuint& shaderProgram) {
  // Create and compile the vertex shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertSrc, NULL);
  glCompileShader(vertexShader);

  // Create and compile the fragment shader
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragSrc, NULL);
  glCompileShader(fragmentShader);

  // Link the vertex and fragment shader into a shader program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
}

void specifySceneVertexAttributes(GLuint shaderProgram) {
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                        0);

  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                        (void*)(3 * sizeof(GLfloat)));

  GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                        (void*)(6 * sizeof(GLfloat)));
}

void specifyScreenVertexAttributes(GLuint shaderProgram) {
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
                        0);

  GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
                        (void*)(2 * sizeof(GLfloat)));
}

// These are now global variables so drawCubeScene() can access them
GLuint vaoCube, sceneShaderProgram, texKitten, texPuppy;
GLint uniSceneModel, uniSceneView, uniColor;

// Draw 3D scene (spinning cube)
void drawCubeScene(const glm::mat4& view, float time) {
  glm::mat4 model;
  model = glm::rotate(model, time * glm::radians(180.0f),
                      glm::vec3(0.0f, 0.0f, 1.0f));
  glUniformMatrix4fv(uniSceneModel, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(uniSceneView, 1, GL_FALSE, glm::value_ptr(view));

  // Draw cube
  glDrawArrays(GL_TRIANGLES, 0, 36);

  glEnable(GL_STENCIL_TEST);

  // Draw floor
  glStencilFunc(GL_ALWAYS, 1, 0xFF);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  glStencilMask(0xFF);
  glDepthMask(GL_FALSE);
  glClear(GL_STENCIL_BUFFER_BIT);

  glDrawArrays(GL_TRIANGLES, 36, 6);

  // Draw cube reflection
  glStencilFunc(GL_EQUAL, 1, 0xFF);
  glStencilMask(0x00);
  glDepthMask(GL_TRUE);

  model = glm::scale(glm::translate(model, glm::vec3(0, 0, -1)),
                     glm::vec3(1, 1, -1));
  glUniformMatrix4fv(uniSceneModel, 1, GL_FALSE, glm::value_ptr(model));

  glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);

  glDisable(GL_STENCIL_TEST);
}

int main() {
  auto t_start = std::chrono::high_resolution_clock::now();

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

  // Create Vertex Array Object
  GLuint vaoCube, vaoPanel;
  glGenVertexArrays(1, &vaoCube);
  glGenVertexArrays(1, &vaoPanel);

  // Create a Vertex Buffer Object and copy the vertex data to it
  GLuint vboCube, vboPanel;
  glGenBuffers(1, &vboCube);
  glGenBuffers(1, &vboPanel);

  glBindBuffer(GL_ARRAY_BUFFER, vboCube);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, vboPanel);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices,
               GL_STATIC_DRAW);

  // Create shader programs
  GLuint sceneVertexShader, sceneFragmentShader, sceneShaderProgram;
  createShaderProgram(sceneVertexSource, sceneFragmentSource, sceneVertexShader,
                      sceneFragmentShader, sceneShaderProgram);

  GLuint panelVertexShader, panelFragmentShader, panelShaderProgram;
  createShaderProgram(panelVertexSource, panelFragmentSource, panelVertexShader,
                      panelFragmentShader, panelShaderProgram);

  // Specify the layout of the vertex data
  glBindVertexArray(vaoCube);
  glBindBuffer(GL_ARRAY_BUFFER, vboCube);
  specifySceneVertexAttributes(sceneShaderProgram);

  glBindVertexArray(vaoPanel);
  glBindBuffer(GL_ARRAY_BUFFER, vaoPanel);
  specifyScreenVertexAttributes(panelShaderProgram);

  // Load textures
  GLuint texKitten = loadTexture("../png/sample.png");
  GLuint texPuppy = loadTexture("../png/sample2.png");
  glUseProgram(sceneShaderProgram);
  glUniform1i(glGetUniformLocation(sceneShaderProgram, "texKitten"), 0);
  glUniform1i(glGetUniformLocation(sceneShaderProgram, "texPuppy"), 1);

  glUseProgram(panelShaderProgram);
  glUniform1i(glGetUniformLocation(panelShaderProgram, "texFramebuffer"), 0);

  // Create framebuffer
  GLuint frameBuffer;
  glGenFramebuffers(1, &frameBuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

  // Create texture to hold color buffer
  GLuint texColorBuffer;
  glGenTextures(1, &texColorBuffer);
  glBindTexture(GL_TEXTURE_2D, texColorBuffer);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE,
               NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         texColorBuffer, 0);

  // Create Renderbuffer Object to hold depth and stencil buffers
  GLuint rboDepthStencil;
  glGenRenderbuffers(1, &rboDepthStencil);
  glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, rboDepthStencil);

  // Set up model, view and projection
  glm::mat4 panelModel;
  panelModel =
      glm::rotate(panelModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  panelModel = glm::translate(panelModel, glm::vec3(0.0f, 0.0f, 2.0f));
  glm::mat4 normalAngleView =
      glm::lookAt(glm::vec3(2.5f, 2.5f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 alternateAngleView =
      glm::lookAt(glm::vec3(2.65f, 0.465f, 0.25f),
                  glm::vec3(-0.5f, 0.0f, -0.45f), glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 proj =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);

  // Set up panel transformation matrices
  GLint uniPanelModel = glGetUniformLocation(panelShaderProgram, "model");
  glUniformMatrix4fv(uniPanelModel, 1, GL_FALSE, glm::value_ptr(panelModel));

  GLint uniPanelView = glGetUniformLocation(panelShaderProgram, "view");
  glUniformMatrix4fv(uniPanelView, 1, GL_FALSE,
                     glm::value_ptr(normalAngleView));

  GLint uniPanelProj = glGetUniformLocation(panelShaderProgram, "proj");
  glUniformMatrix4fv(uniPanelProj, 1, GL_FALSE, glm::value_ptr(proj));

  // Set up 3D scene transformation matrices
  glUseProgram(sceneShaderProgram);

  uniSceneModel = glGetUniformLocation(sceneShaderProgram, "model");
  uniSceneView = glGetUniformLocation(sceneShaderProgram, "view");
  GLint uniSceneProj = glGetUniformLocation(sceneShaderProgram, "proj");
  glUniformMatrix4fv(uniSceneProj, 1, GL_FALSE, glm::value_ptr(proj));

  uniColor = glGetUniformLocation(sceneShaderProgram, "overrideColor");

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    // Calculate transformation
    auto t_now = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(
                     t_now - t_start)
                     .count();

    // Bind our framebuffer and clear the screen to white
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw 3D scene (spinning cube) from alternate angle
    glBindVertexArray(vaoCube);
    glUseProgram(sceneShaderProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texKitten);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texPuppy);

    drawCubeScene(alternateAngleView, time);

    // Bind default framebuffer and clear the screen to cornflower blue
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the panel, textured with the contents of our framebuffer
    glBindVertexArray(vaoPanel);
    glUseProgram(panelShaderProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Draw 3D scene again from normal angle
    glBindVertexArray(vaoCube);
    glUseProgram(sceneShaderProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texKitten);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texPuppy);

    drawCubeScene(normalAngleView, time);

    // swap buffers
    glfwSwapBuffers(window);
  }

  // tear down
  glDeleteRenderbuffers(1, &rboDepthStencil);
  glDeleteTextures(1, &texColorBuffer);
  glDeleteFramebuffers(1, &frameBuffer);
  glDeleteTextures(1, &texPuppy);
  glDeleteTextures(1, &texKitten);
  glDeleteProgram(panelShaderProgram);
  glDeleteShader(panelFragmentShader);
  glDeleteShader(panelVertexShader);
  glDeleteProgram(sceneShaderProgram);
  glDeleteShader(sceneFragmentShader);
  glDeleteShader(sceneVertexShader);
  glDeleteBuffers(1, &vboCube);
  glDeleteBuffers(1, &vboPanel);
  glDeleteVertexArrays(1, &vaoCube);
  glDeleteVertexArrays(1, &vaoPanel);
  glfwTerminate();

  return 0;
}
