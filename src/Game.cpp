
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

bool Game::init()
{

  return true;
}

void Game::update(float dt)
{

}

void Game::render()
{

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


