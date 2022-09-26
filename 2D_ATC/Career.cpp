#include "Career.h"

Career::Career()
{
	initSounds();
	initFonts();
	initButtons();
	initInputs();
	initFlags();
	initText();

	drawCreateCareer = false;
	careerCreated = false;
	flagIndex = -1;
}

void Career::update(sf::Vector2i mousePosition)
{
	this->mousePosition = mousePosition;

	if (drawCreateCareer)
	{
		playerName.update(mousePosition);

		submitButton.CheckMouseHover(mousePosition);
	}

	cancelButton.CheckMouseHover(mousePosition);

	return;
}

void Career::render(sf::RenderTarget* window)
{
	if (drawCreateCareer)
	{
		playerName.render(window);

		for (int i = 0; i < FLAGS; i++)
		{
			window->draw(flagsSprite[i]);
		}

		window->draw(countrySelectedInfo);

		submitButton.render(window);
	}

	cancelButton.render(window);

	return;
}

void Career::LoadCareer()
{
	in = std::ifstream("../Resources/Career/careerData.txt");

	in >> _playerName;
	in >> selectedMap;
	in >> atcPosition;

	in.close();
	careerCreated = true;

	return;
}

void Career::HandleClick()
{
	if (cancelButton.isButtonClicked(mousePosition))
	{
		buttonClickSound.play();

		if (drawCreateCareer)
			drawCreateCareer = false;

	}
	else if(submitButton.isButtonClicked(mousePosition))
	{
		out = std::ofstream("../Resources/Career/careerData.txt");
		if (playerName.GetInputData().length() == 0)
		{
			_playerName = "newCareer";
		}
		else
		{
			_playerName = playerName.GetInputData();
		}
		
		if (flagIndex == -1)
			flagIndex = rand() % FLAGS;

		out << _playerName << '\n';
		out << flags[flagIndex] << '\n';
		out << "ground" << '\n';

		out.close();

		careerCreated = true;
	}
	else
	{
		for (int i = 0; i < FLAGS; i++)
		{
			if (flagsSprite[i].getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
			{
				flagIndex = i;
				std::string country = flags[i];
				selectedMap = flags[i];
				country[0] = std::toupper(country[0]);

				countrySelectedInfo.setString(country + " has been selected.");
			}
		}
	}


	return;
}

void Career::HandleInput(unsigned unicode)
{
	playerName.HandleInput(unicode);

	return;
}

bool Career::isCareerCreated()
{
	return careerCreated;
}

void Career::initSounds()
{
	buttonClickBuffer.loadFromFile("../Resources/sounds/buttonClick.wav");

	buttonClickSound.setBuffer(buttonClickBuffer);

	return;
}

void Career::initButtons()
{
	cancelButton = Button(sf::Vector2f(300, 90), sf::Vector2f(400, 750));
	submitButton = Button(sf::Vector2f(300, 90), sf::Vector2f(800, 750));

	cancelButton.SetDefaultColor(sf::Color(24, 25, 26, 255));
	cancelButton.SetBorder(2, sf::Color::White);
	
	submitButton.SetDefaultColor(sf::Color(24, 25, 26, 255));
	submitButton.SetBorder(2, sf::Color::White);
	
	return;
}

void Career::initFonts()
{
	comfortaa.loadFromFile("../Resources/fonts/Comfortaa-Regular.ttf");

	return;
}

void Career::initInputs()
{
	playerName.setSize(sf::Vector2f(700, 50));
	playerName.setBackgroundColor(sf::Color(29, 30, 31));
	playerName.setPosition(sf::Vector2f(600, 300));
	playerName.setBorderColor(sf::Color::White);
	playerName.setBorderThickness(1);
	playerName.setInputDescription("YOUR NAME");
	playerName.setMaxChars(45);
	playerName.setCharactersSize(15);

	return;
}

void Career::initFlags()
{
	for (int i = 0; i < 1; i++)
	{
		flagTexture.loadFromFile("../Resources/images/flags/"+ flags[i]+".png");
		flagsSprite[i].setTexture(flagTexture);
		setFlag(i);
	}


	return;
}

void Career::initText()
{
	countrySelectedInfo.setFont(comfortaa);
	countrySelectedInfo.setCharacterSize(35);
	countrySelectedInfo.setPosition(sf::Vector2f(100, 600));

	return;
}

void Career::setFlag(unsigned flagId)
{
	flagsSprite[flagId].setScale(sf::Vector2f(0.1f, 0.1f));

	if (flagId <= 15)
	{
		flagsSprite[flagId].setPosition(sf::Vector2f(flagId * 70 + 15, 370));
	}
	else
	{

	}

	return;
}
