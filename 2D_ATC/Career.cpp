#include "Career.h"

Career::Career()
{
	initSounds();
	initFonts();
	initButtons();
	initInputs();

	drawLoadCareer = false;
	drawCreateCareer = false;
	careerCreated = false;
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

		submitButton.render(window);
	}

	cancelButton.render(window);

	return;
}

void Career::LoadCareer()
{

	return;
}

void Career::CreateCareer()
{

	return;
}

void Career::HandleClick()
{
	if (cancelButton.isButtonClicked(mousePosition))
	{
		buttonClickSound.play();

		if (drawLoadCareer)
			drawLoadCareer = false;
		else if (drawCreateCareer)
			drawCreateCareer = false;

	}
	else if(submitButton.isButtonClicked(mousePosition))
	{
		out = std::ofstream("../Resources/Career/careerData.txt");
		if (playerName.inputDataString.length() == 0)
			out << "newCareer\n";
		else
			out << playerName.inputDataString<<'\n';
		out.close();
		careerCreated = true;
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
	cancelButton.setSize(sf::Vector2f(300, 90));
	cancelButton.setPosition(sf::Vector2f(400, 750));
	cancelButton.setDefaultColor(sf::Color(24, 25, 26, 255));
	cancelButton.setBorderColor(sf::Color::White);
	cancelButton.setBorderThickness(2);
	cancelButton.setText(&comfortaa, "Cancel");
	cancelButton.setTextInMiddle();

	submitButton.setSize(sf::Vector2f(300, 90));
	submitButton.setPosition(sf::Vector2f(800, 750));
	submitButton.setDefaultColor(sf::Color(24, 25, 26, 255));
	submitButton.setBorderColor(sf::Color::White);
	submitButton.setBorderThickness(2);
	submitButton.setText(&comfortaa, "Submit");
	submitButton.setTextInMiddle();

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
