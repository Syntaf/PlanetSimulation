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

PlanetManager::PlanetManager(int maxplanets):
	d_MAXPLANETS(maxplanets)
{
	// allocate resources needed for OpenGL buffers
	g_planet_position_size_data = new GLfloat[d_MAXPLANETS * 4];
	g_planet_color_data = new GLubyte[d_MAXPLANETS * 4];

	//generate and bind vertex array
	glGenVertexArrays(1, &d_vertex_array_id);
	glBindVertexArray(d_vertex_array_id);
}

PlanetManager::~PlanetManager()
{
	//free dynamic and OpenGL memory
	glDeleteBuffers(1, &d_planet_color_buffer);
	glDeleteBuffers(1, &d_planet_position_buffer);
	glDeleteBuffers(1, &d_billboard_vertex_buffer);
	delete [] g_planet_color_data;
	delete [] g_planet_position_size_data;
}

void PlanetManager::initPlanets()
{
	//create planets in square shape
	int max_planets = (int)sqrt(d_MAXPLANETS);
    for(int i=0; i<max_planets; i++) {
        for(int j=0; j<max_planets; j++) {
            Planet planet;
			auto factor_x = (i - (float)max_planets / 2.0f) / (float)max_planets;
			auto factor_y = (j - (float)max_planets / 2.0f) / (float)max_planets;

			//multiply by arbitrary constant
			glm::vec2 particle_locale_delta = glm::vec2(30  * factor_x, 30 * factor_y);
			glm::vec2 d2Pos = glm::vec2(0, 0);
			d2Pos += particle_locale_delta;
            planet.pos = glm::vec3(d2Pos.x,d2Pos.y,-70);

            planet.cameradistance = -1.0f;

            planet.r = 255;
            planet.g = 50;
            planet.b = 100;
            planet.a = 255;

            planet.size = 1.0f;
            d_planet_container.push_back(planet);
        }
    }
}

bool PlanetManager::loadTexture(const std::string& filename)
{
	if(!(d_texture = loadDDS("textures/Planet.dds"))) {
		std::cout << "Unable to locate texture " << filename << std::endl;
		return false;
	}
	return true;
}

void PlanetManager::genGLBuffers()
{
	glGenBuffers(1, &d_billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, d_billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &d_planet_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, d_planet_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, d_MAXPLANETS * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	glGenBuffers(1, &d_planet_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, d_planet_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, d_MAXPLANETS * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
}

void PlanetManager::fillPlanetGLBuffers(const int& index, const int& planet_count)
{
	//P is a shortcut so we don't have to type d_planet_container[index] a lot
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

void PlanetManager::updateGLBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, d_planet_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, d_MAXPLANETS * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, d_MAXPLANETS * 4 * sizeof(GLfloat), g_planet_position_size_data);

	glBindBuffer(GL_ARRAY_BUFFER, d_planet_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, d_MAXPLANETS * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, d_MAXPLANETS * 4 * sizeof(GLubyte), g_planet_color_data);
}

void PlanetManager::activateTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, d_texture);
}

void PlanetManager::updatePlanets(const float& delta, glm::mat4& projection_matrix,
								glm::mat4& view_matrix)
{
	//TODO : write planet update function
	GLsizei planet_count=0;
	for(size_t i = 0; i < d_planet_container.size(); i++) {
		Planet &p = d_planet_container[i];
		p.pos = glm::vec3(0.0f,0.0f,0);
		fillPlanetGLBuffers(int(i), planet_count);
		planet_count++;
	}
	updateGLBuffers();
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
	glVertexAttribDivisor(2, 1);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, d_MAXPLANETS);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}