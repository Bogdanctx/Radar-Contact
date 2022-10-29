#include "NewGame.h"
#include <cstring>
#include <filesystem>
#include <fstream>

#define flagX 75
#define flagY 250

NewGame::NewGame()
{

}

NewGame::NewGame(AssetsManager assetsManager)
{
	this->assetsManager = assetsManager;

	draw = applyGame = 0;

	initButtons();
	initSounds();
	initFlags();
	initText();
}

void NewGame::initFlags()
{
	std::string path = "../Resources/images/flags";

	for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
	{
		std::string flagName = entry.path().filename().generic_string();
		
		sf::Texture *t = new sf::Texture();
		t->loadFromFile(path + '/' + flagName);

		flagName.erase(flagName.length() - 4);

		flags.push_back(Flag(t, sf::Vector2f(
			flagX + flags.size() * 105, flagY
		), &assetsManager.GetFont("MerriweatherSans-Regular.ttf"), flagName));
	}

	return;
}

void NewGame::initText()
{
	countrySelected.setFont(assetsManager.GetFont("MerriweatherSans-Regular.ttf"));
	countrySelected.setCharacterSize(30);
	countrySelected.setPosition(sf::Vector2f(10, 780));

	return;
}

void NewGame::render(sf::RenderTarget* window)
{
	apply.render(window);
	cancel.render(window);

	for (auto& it : flags)
	{
		window->draw(it.sprite);
		window->draw(it.text);
	}

	window->draw(countrySelected);

	return;
}

void NewGame::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	apply.CheckMouseHover(mousePosition);
	cancel.CheckMouseHover(mousePosition);

	return;
}

void NewGame::HandleClick()
{
	if (apply.isButtonClicked(mousePosition))
	{
		applyGame = 1;

		buttonClickSound.play();
	}
	else if (cancel.isButtonClicked(mousePosition))
	{
		draw = false;
		buttonClickSound.play();
	}
	else
	{
		for (auto& it : flags)
		{
			if (it.sprite.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
			{
				std::ofstream write("../Resources/game.txt");
				write << it.country;
				write.close();

				countrySelected.setString(it.text.getString() + " has been selected.");

				break;
			}
		}
	}

	return;
}

void NewGame::initButtons()
{
	apply = Button(sf::Vector2f(300, 90), sf::Vector2f(335, 650));
	cancel = Button(sf::Vector2f(300, 90), sf::Vector2f(835, 650));

	apply.SetDefaultColor(sf::Color(24, 25, 26, 255));
	apply.SetBorder(2, sf::Color::White);
	apply.SetText(&assetsManager.GetFont("Comfortaa-Regular.ttf"), "Apply");
	apply.CenterText();

	cancel.SetDefaultColor(sf::Color(24, 25, 26, 255));
	cancel.SetBorder(2, sf::Color::White);
	cancel.SetText(&assetsManager.GetFont("Comfortaa-Regular.ttf"), "Cancel");
	cancel.CenterText();

	return;
}

void NewGame::initSounds()
{
	buttonClickSound.setBuffer(assetsManager.GetSoundBuffer("buttonClick.wav"));

	return;
}

NewGame::Flag::Flag(sf::Texture* texture, sf::Vector2f position, sf::Font *font, std::string name)
{
	country = name;
	for (int i = 0; i < name.length(); i++) name[i] = std::toupper(name[i]);

	this->texture = texture;
	sprite.setTexture(*texture);

	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.setOrigin(sf::Vector2f(
		bounds.left + bounds.width / 2,
		bounds.top + bounds.height / 2
	));
	sprite.setScale(sf::Vector2f(0.13f, 0.13f));
	sprite.setPosition(position);

	text.setString(name);
	text.setCharacterSize(10);
	text.setFont(*font);
	position.y += 30;
	position.x -= text.getLocalBounds().width / 2;
	text.setPosition(position);
}
