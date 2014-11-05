#ifndef APP_H_
#define APP_H_

#include "GL/glew.h"
#include <SFML/Graphics.hpp>

class App{
  public:
    App(sf::VideoMode mode);
    App();
    ~App();

    void run();

  private:
	sf::Clock clock;
    sf::Window d_main_window;
    bool running;
};

#endif