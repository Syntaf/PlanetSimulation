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
#include "app.hpp"

App::App(sf::VideoMode mode):
	running(true)
{
  d_main_window.create(mode,
    "Planet Simulator",
    sf::Style::Default,
    sf::ContextSettings(32, 8, 0, 3,3 )
  );

  d_main_window.setPosition(sf::Vector2i(500,50));
}

App::App()
{
  d_main_window.create(sf::VideoMode(800,600),
    "Planet Simulator",
    sf::Style::Default,
    sf::ContextSettings(32, 8, 0, 3, 3)
  );

  d_main_window.setPosition(sf::Vector2i(500,50));
}

App::~App()
{
  //nothing atm
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
	d_cameraup_worldspace_id = glGetUniformLocation(d_program_id, "CameraUp_wordspace");
	d_viewprojmatrix_id = glGetUniformLocation(d_program_id, "VP");

	d_texture_id = glGetUniformLocation(d_program_id, "myTextureSampler");
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

        d_main_window.display();
    }
}
