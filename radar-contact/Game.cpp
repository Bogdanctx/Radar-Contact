#include "Game.h"

Game::Game()
{

}

Game::Game(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;

	isActive = true;

	initObjects();
}

void Game::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	controlArea.update(mousePosition);

	if(t_airplaneSpawn.getElapsedTime().asSeconds() >= 10)
    {
        CreateAirplane();
        t_airplaneSpawn.restart();
    }
}

void Game::CreateAirplane()
{
    Airplane airplane = Airplane(assetsManager);
    airplanes.push_back(airplane);
}

void Game::render(sf::RenderTarget* window)
{
	map.render(window);
	controlArea.render(window);
}

void Game::processEvents(sf::Event event)
{
	switch (event.type)
	{

	}
}

void Game::initObjects()
{
	map = Map(assetsManager);
	controlArea = ControlArea(assetsManager);
}
