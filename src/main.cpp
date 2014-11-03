#include <iostream>
#include <vector>
#include "MassObject.h"

int main()
{
  App app(sf::VideoMode(800,600));
  std::vector<MassObject> two_objects = {MassObject(0.0f, 0.0f, 0.0f, 5.9722e+24f), MassObject(6378.1e3f, 0.0f, 0.0f, 1.0f)};

  float f = two_objects[0].gravitationalForce(two_objects[1]);
  std::cout << "Force between two objects: " << f << std::endl;
  return 0;
}
