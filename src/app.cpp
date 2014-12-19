#include <iostream>
#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include "common/shader.hpp"
#include "common/texture.hpp"
#include "common/controls.hpp"
#include "app.hpp"

bool App::running=true;

App::App(sf::VideoMode mode)
{
  d_main_window.create(mode,
    "Planet Simulator",
    sf::Style::Default,
    sf::ContextSettings(32, 8, 0, 3,3 )
  );

  d_main_window.setPosition(sf::Vector2i(500,50));
}

App::~App()
{
	delete d_planet_manager;
	glDeleteProgram(d_program_id);
}

bool App::initGL(const int& planet_count)
{
	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW\n";
		return false;
	}

	d_planet_manager = new PlanetManager(&d_main_window, planet_count);

	d_planet_manager->genGLBuffers();
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

	d_program_id = LoadShaders("shaders/vertexshader.vert",
		"shaders/fragmentshader.frag");

	d_cameraright_worldspace_id = glGetUniformLocation(d_program_id, "CameraRight_worldspace");
	d_cameraup_worldspace_id = glGetUniformLocation(d_program_id, "CameraUp_worldspace");
	d_viewprojmatrix_id = glGetUniformLocation(d_program_id, "VP");

	d_texture_id = glGetUniformLocation(d_program_id, "myTextureSampler");
	return true;
}

bool App::initPlanets(const std::string& texture_path)
{
	if(!(d_planet_manager->loadTexture(texture_path.c_str())))
		return false;
	d_planet_manager->initPlanets();
	return true;
}

void App::run()
{
    while( running )
    {
        float delta = clock.restart().asSeconds();
        //handle window events
        sf::Event event;
        while(d_main_window.pollEvent(event))
        {
          if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            running = false;
          else if(event.type == sf::Event::Resized)
            glViewport(0,0,event.size.width,event.size.height);
        }

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		computeMatricesFromInputs(d_main_window, delta);
		glm::mat4 projection_matrix = getProjectionMatrix();
		glm::mat4 view_matrix = getViewMatrix();
		glm::mat4 view_projection_matrix = projection_matrix * view_matrix;

		d_planet_manager->updatePlanets(delta, projection_matrix, view_matrix);

		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glUseProgram(d_program_id);

		d_planet_manager->activateTexture();

		glUniform1i(d_texture_id, 0);

		glUniform3f(d_cameraright_worldspace_id, view_matrix[0][0], view_matrix[1][0], view_matrix[2][0]);
		glUniform3f(d_cameraup_worldspace_id, view_matrix[0][1], view_matrix[1][1], view_matrix[2][1]);

		glUniformMatrix4fv(d_viewprojmatrix_id, 1, GL_FALSE, &view_projection_matrix[0][0]);

		d_planet_manager->drawPlanets();
        d_main_window.display();
    }
}
