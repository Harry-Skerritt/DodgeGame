
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init() {
  glow.init(
    {50, 50},
    sf::Color(100, 100, 0, 255),
    sf::Color::White,
    20.f);

  return true;
}

void Game::update(float dt)
{
  //shader.setUniform("u_time", shader_clock.getElapsedTime().asSeconds());
  glow.setPosition(glow.getPosition().x + 50.f * dt, glow.getPosition().y);
}

void Game::render()
{
  window.draw(glow);
}


void Game::mouseClicked(sf::Event event)
{
	
}
    

void Game::mouseReleased(sf::Event event)
{
  
}

void Game::keyPressed(sf::Event event)
{

}

void Game::keyReleased(sf::Event event)
{

}

void Game::mouseScroll(sf::Event event)
{
  
}

void Game::mouseDragged(sf::Event event)
{

}


