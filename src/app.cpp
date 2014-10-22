#include <iostream>
#include <cstdlib>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include "common/shader.hpp"
#include "common/texture.hpp"

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
  //nothing atm
}
