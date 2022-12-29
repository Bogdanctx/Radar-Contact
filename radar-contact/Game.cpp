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

	if(t_airplaneSpawn.getElapsedTime().asSeconds() >= 4)
    {
        CreateAirplane();
        t_airplaneSpawn.restart();
    }

    for(auto &it: airplanes)
    {
        it.update(mousePosition);

        if(controlArea.isInArea(it.airplane.getPosition()))
        {
            it.isInControlArea = true;
        }
        else
        {
            if(it.isInControlArea == true)
            {

            }
        }
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

    for(auto it: airplanes)
        it.render(window);
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
