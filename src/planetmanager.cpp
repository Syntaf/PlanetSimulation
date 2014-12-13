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

PlanetManager::PlanetManager(sf::Window* parent_window, int maxplanets):
	d_maxplanets(maxplanets)
{
	d_parent_window = parent_window;
	
	g_planet_position_size_data = new GLfloat[d_maxplanets * 4];
	g_planet_color_data = new GLubyte[d_maxplanets * 4];

	glGenVertexArrays(1, &d_vertex_array_id);
	glBindVertexArray(d_vertex_array_id);
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
	Planet one_planet;
	glm::vec2 d2Pos = glm::vec2(5, 5);
	one_planet.pos = glm::vec3(d2Pos.x, d2Pos.y, -70.0f);

	one_planet.size = 10.0f;
	d_planet_container.push_back(one_planet);
}

bool PlanetManager::loadTexture(const std::string& filename)
{
	if(!(d_texture = loadDDS("textures/Particle.DDS")))
		return false;
	return true;
}

void PlanetManager::genGLBuffers()
{
	glGenBuffers(1, &d_billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, d_billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &d_planet_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, d_planet_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, d_maxplanets * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	glGenBuffers(1, &d_planet_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, d_planet_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, d_maxplanets * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
}

void PlanetManager::fillPlanetGLBuffers(const int& index, const int& planet_count)
{
	Planet &p = d_planet_container[index];
	//Fill GPU buffer
	g_planet_position_size_data[4*planet_count+0] = p.pos.x;
	g_planet_position_size_data[4*planet_count+1] = p.pos.y;
	g_planet_position_size_data[4*planet_count+2] = p.pos.z;
	g_planet_position_size_data[4*planet_count+3] = p.size;

	g_planet_color_data[4*planet_count+0] = p.r;
	g_planet_color_data[4*planet_count+1] = p.g;
	g_planet_color_data[4*planet_count+2] = p.b;
	g_planet_color_data[4*planet_count+3] = p.a;
}

void PlanetManager::updateGlBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, d_planet_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, d_maxplanets * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, d_maxplanets * 4 * sizeof(GLfloat), g_planet_position_size_data);

	glBindBuffer(GL_ARRAY_BUFFER, d_planet_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, d_maxplanets * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, d_maxplanets * 4 * sizeof(GLubyte), g_planet_color_data);
}

void PlanetManager::activateTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, d_texture);
}

void PlanetManager::updatePlanets(const float& delta, glm::mat4& projection_matrix,
								glm::mat4& view_matrix)
{
	//do nothing atm
}

void PlanetManager::drawPlanets()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, d_billboard_vertex_buffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, d_planet_position_buffer);
	glVertexAttribPointer(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, d_planet_color_buffer);
	glVertexAttribPointer(
		2,
		4,
		GL_UNSIGNED_BYTE,
		GL_TRUE,
		0,
		(void*)0
	);

	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 2);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, d_maxplanets);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}