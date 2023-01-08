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
	map.update(mousePosition);

	if (airplanes.size() == 0)
		CreateAirplane();

	/*if (t_airplaneSpawn.getElapsedTime().asSeconds() >= 4)
    {
        CreateAirplane();
        t_airplaneSpawn.restart();
    }*/

    for(auto &it: airplanes)
    {
        it.update(mousePosition);
    }
}

void Game::CreateAirplane()
{
    Airplane airplane = Airplane(&assetsManager, controlArea);
    airplanes.push_back(airplane);
}

void Game::render(sf::RenderTarget* window)
{
	map.render(window);
	controlArea.render(window);

	for (auto it : airplanes)
	{
		it.render(window);
	}
}

void Game::processEvents(sf::Event event)
{
	for (auto &it : airplanes)
	{
		it.processEvents(event);
	}

	switch (event.type)
	{
		default:
			break;
	}
}

void Game::initObjects()
{
	map = Map(assetsManager);
	controlArea = ControlArea(assetsManager);
}
