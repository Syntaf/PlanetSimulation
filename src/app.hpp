#ifndef APP_H_
#define APP_H_

#include "GL/glew.h"
#include "planetmanager.hpp"
#include <SFML/Graphics.hpp>

class App{
  public:
	//The constructor of App does not actually do much other than
	//	create the main window and set it's position to the middle
	//  of the screen.
	//  TODO? make constructor call initGL and initPlanets by itself
    App(sf::VideoMode mode);
    ~App();

	//Initialize all openGL related components for the program, this
	//	function will be called before initPlanets, as it creates the
	//	foundation of the program. It will clear the screen, ensure GLEW
	//	is working, create buffers, load shaders and more.
	bool initGL(const int& planet_count);

	//Initialize the initial state and values of all planets
	//	that are too be rendered on the screen in the first frame
	//	of the program. This function does very little itself, but
	//	calls the manager's `initPlanets` function which sets the 
	//	initial position, size, color, etc. of each planet.
	bool initPlanets(const std::string& texture_path);

	//The main loop of the entire program, run is responsible for
	//	handling window events, receiving user input, calculating the
	//	delta time for movement and render our planets to the screen.
	//	The internal position calculation and such is done inside of 
	//	the planet manager class.
    void run();

  private:
	sf::Clock clock;						// calculate delta time
    sf::Window d_main_window;				// main window of program

	PlanetManager *d_planet_manager;		// our planet mamanger, dynamically allocated

	GLuint d_program_id;					// only one OpenGL program is used
	GLuint d_cameraright_worldspace_id;		// vector to be passed into the shader
	GLuint d_cameraup_worldspace_id;		// additional vector to be passed to shader
	GLuint d_viewprojmatrix_id;				// view projection matrix to be passed to shader

	GLuint d_texture_id;					// id of the texture(s)


    static bool running;					// we only ever want one program running,
											// unless you like making things difficult
};

#endif