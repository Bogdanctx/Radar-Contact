#include "Settings.h"

Settings::Settings()
{

}

Settings::Settings(AssetsManager* assetsManager)
{
	this->assetsManager = assetsManager;

	initSounds();
	initButtons();

	draw = false;
}

void Settings::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	applyButton.CheckMouseHover(mousePosition);

	return;
}

void Settings::render(sf::RenderTarget* window)
{
	applyButton.render(window);

	return;
}

void Settings::HandleClick()
{
	if (applyButton.isButtonClicked(mousePosition))
	{
		buttonClickSound.play();
		draw = false;
	}

	return;
}

void Settings::initSounds()
{
	buttonClickSound.setBuffer(assetsManager->GetSoundBuffer("buttonClick.wav"));

	return;
}

void Settings::initButtons()
{
	applyButton = Button(sf::Vector2f(300, 90), sf::Vector2f(600, 750));

	applyButton.SetDefaultColor(sf::Color(24, 25, 26, 255));
	applyButton.SetBorder(2, sf::Color::White);
	applyButton.SetText(&assetsManager->GetFont("Comfortaa-Regular.ttf"), "Apply");
	applyButton.CenterText();

	return;
}