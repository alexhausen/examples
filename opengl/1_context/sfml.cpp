// https://open.gl/context

// create a window context with SFML
// g++ -std=c++17 -Wall -Wextra -Werror -pedantic sfml.cpp -lsfml-system -lsfml-window -lGLEW -lGL

#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main() {

  // create window context using SFML
  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.antialiasingLevel = 2; // Optional
  sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Close, settings);

  // portable way to access GL buffers
  glewExperimental = GL_TRUE;
  glewInit();
  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  printf("%u\n", vertexBuffer);

  bool running = true;
  while (running) {
    sf::Event windowEvent;
    while (window.pollEvent(windowEvent)) {
      switch (windowEvent.type) {
      case sf::Event::Closed:
        running = false;
        break;

      case sf::Event::KeyPressed:
        if (windowEvent.key.code == sf::Keyboard::Escape)
          running = false;
        break;
      
      default:
        break;
      }
    }
  }
  return 0;
}