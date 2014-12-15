#ifndef PLANETMANAGER_H_
#define PLANETMANAGER_H_

#include "planet.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class PlanetManager{
	public:
		PlanetManager(sf::Window* parent_window, int maxplanets=20);
		~PlanetManager();

		//planet initialization functions
		void initPlanets();
		bool loadTexture(const std::string& filename);

		//OpenGL buffer functions 
		void genGLBuffers();
		void fillPlanetGLBuffers(const int& index, const int& planet_count);
		void updateGlBuffers();

		//activate OpenGL texture for drawing to screen
		void activateTexture();

		//update position of planets and also update OpenGL buffers
		void updatePlanets(const float& delta, glm::mat4& projection_matrix,
				glm::mat4& view_matrix);

		//draw planets to screen
		void drawPlanets();

	private:
		//pointer to parent window
		sf::Window *d_parent_window;

		//vector of planets
		std::vector<Planet> d_planet_container;

		//openGL buffer data, texture id and vertex array id
		GLuint d_vertex_array_id;
		GLuint d_texture_id;
		GLuint d_billboard_vertex_buffer;
		GLuint d_planet_position_buffer;
		GLuint d_planet_color_buffer;
		
		GLuint d_texture;

		//data
		GLfloat* g_planet_position_size_data;
		GLubyte* g_planet_color_data;

		static const GLfloat g_vertex_buffer_data[];

		//custom 'constants'
		int d_maxplanets;
};

#endif