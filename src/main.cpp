#include <iostream>
#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "app.hpp"
#include "MassObject.hpp"

int main(int argc, char* argv[]) {
  App app(sf::VideoMode(800,600));
  std::vector<MassObject> two_objects;
  two_objects.push_back(MassObject(0.0f, 0.0f, 0.0f, 5.9722e+24f));
  two_objects.push_back(MassObject(6378.1e3f, 0.0f, 0.0f, 1.0f));

  float f = two_objects[0].gravitationalForce(two_objects[1]);
  std::cout << "Force between two objects: " << f << std::endl;
  return 0;
}
