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
