#ifndef APP_H_
#define APP_H_

#include "GL/glew.h"
#include "planetmanager.hpp"
#include <SFML/Graphics.hpp>

class App{
  public:
    App(sf::VideoMode mode);
    App();
    ~App();

	bool initGL(const int& planet_count);

	bool initPlanets(const std::string& texture_path);

    void run();

  private:
	sf::Clock clock;
    sf::Window d_main_window;

	PlanetManager *d_planet_manager;

	GLuint d_program_id;
	GLuint d_cameraright_worldspace_id;
	GLuint d_cameraup_worldspace_id;
	GLuint d_viewprojmatrix_id;

	GLuint d_texture_id;


    bool running;
};

#endif