#include "Game.h"

Game::Game()
{

}

Game::Game(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;

	isActive = true;
}

void Game::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;
}

void Game::render(sf::RenderTarget* window)
{
	map.render(window);
}

void Game::processEvents(sf::Event event)
{
	switch (event.type)
	{
		
	}
}
