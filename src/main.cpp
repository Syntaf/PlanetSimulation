#include <iostream>
#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "app.hpp"

int main(int argc, char* argv[]) 
{
	App program(sf::VideoMode(1000, 750));

	if( !program.initGL(1) || !program.initPlanets("textures/Planet.dds"))
		return -1;

	program.run();

	return 0;
}
