#include "ContinueGame.h"

ContinueGame::ContinueGame()
{

}

ContinueGame::ContinueGame(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;

	option = draw = 0;

	initButtons();
	initSounds();
}

void ContinueGame::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	playTower.CheckMouseHover(mousePosition);
	playRadar.CheckMouseHover(mousePosition);
	cancel.CheckMouseHover(mousePosition);

	return;
}

void ContinueGame::HandleClick()
{
	if (playTower.isButtonClicked(mousePosition))
	{
		option = 1;
		buttonClickSound.play();
	}
	else if (playRadar.isButtonClicked(mousePosition))
	{
		option = 2;
		buttonClickSound.play();
	}
	else if(cancel.isButtonClicked(mousePosition))
	{
		draw = 0;
		buttonClickSound.play();
	}

	return;
}

void ContinueGame::render(sf::RenderTarget* window)
{
	playTower.render(window);
	playRadar.render(window);
	cancel.render(window);

	return;
}

void ContinueGame::initButtons()
{
	playTower = Button(sf::Vector2f(300, 90), sf::Vector2f(335, 400));
	playRadar = Button(sf::Vector2f(300, 90), sf::Vector2f(835, 400));
	cancel = Button(sf::Vector2f(300, 90), sf::Vector2f(600, 650));

	playTower.SetDefaultColor(sf::Color(24, 25, 26, 255));
	playTower.SetBorder(2, sf::Color::White);
	playTower.SetText(&assetsManager.GetFont("Comfortaa-Regular.ttf"), "Play as Tower");
	playTower.CenterText();

	playRadar.SetDefaultColor(sf::Color(24, 25, 26, 255));
	playRadar.SetBorder(2, sf::Color::White);
	playRadar.SetText(&assetsManager.GetFont("Comfortaa-Regular.ttf"), "Play as Radar");
	playRadar.CenterText();

	cancel.SetDefaultColor(sf::Color(24, 25, 26, 255));
	cancel.SetBorder(2, sf::Color::White);
	cancel.SetText(&assetsManager.GetFont("Comfortaa-Regular.ttf"), "Cancel");
	cancel.CenterText();

	return;
}

void ContinueGame::initSounds()
{
	buttonClickSound.setBuffer(assetsManager.GetSoundBuffer("buttonClick.wav"));

	return;
}