#include <iostream>
#include <string>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include "common/controls.hpp"
#include "common/texture.hpp"
#include "planetmanager.hpp"
#include "planet.hpp"

const GLfloat PlanetManager::g_vertex_buffer_data[] = {
         -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
         -0.5f,  0.5f, 0.0f,
          0.5f,  0.5f, 0.0f,
};

PlanetManager::PlanetManager(sf::window* parent_window, int maxplanets):
	d_maxplanets(maxplanets)
{
	d_parent_window = parent_window;
	
	g_particle_position_size_data = new GLfloat[d_maxplanets * 4];
	g_particle_color_data = new GLubyte[d_maxplanets * 4];

	glGenVertexArrays(1, &d_vertex_array_id);
	glBindVertexArrays(d_vertex_array_id);
}

PlanetManager::~PlanetManager()
{
	glDeleteBuffers(1, &d_planet_color_buffer);
	glDeleteBuffers(1, &d_planet_position_buffer);
	glDeleteBuffers(1, &d_billboard_vertex_buffer);
	delete [] g_planet_color_data;
	delete [] g_planet_position_size_data;
}

void PlanetManager::initPlanets()
{

}

void PlanetManager::loadTexture(const std::string& filename)
{

}

void PlanetManager::genGLBuffers()
{

}

void PlanetManager::fillPlanetGLBuffers(const int& index, const int& planet_count)
{

}

void PlanetManager::drawPlanets()
{

}