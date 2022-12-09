#include "Play.h"

Play::Play()
{

}

Play::Play(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;

	isActive = false;

	initObjects();
}

void Play::processEvents(sf::Event event)
{
	switch (event.type)
	{

	}
}

void Play::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;
}

void Play::render(sf::RenderTarget* window)
{
	
}

void Play::initObjects()
{

}