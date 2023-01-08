#include "Airplane.h"

Airplane::Airplane()
{

}

Airplane::Airplane(AssetsManager *assetsManager, ControlArea controlArea)
{
    this->assetsManager = assetsManager;
    this->controlArea = controlArea;

    initShapes();
    initData();

    unsigned short screenSpawn = rand() % 4;
    switch(screenSpawn)
    {
        case 0: // upper screen
        {
            airplane.setPosition(rand() % assetsManager->getResolution().width, 0);
            break;
        }
        case 1: // left screen
        {
            airplane.setPosition(0, rand() % assetsManager->getResolution().height);
            break;
        }
        case 2: // bottom screen
        {
            airplane.setPosition(rand() % assetsManager->getResolution().width, assetsManager->getResolution().height);
            break;
        }
        case 3:
        {
            airplane.setPosition(assetsManager->getResolution().width, rand() % assetsManager->getResolution().height);
            break;
        }
    }

    airplane.setPosition(500, 500);

    velocity = (float)(rand() % 200 + 100)/100;
    heading = Math::DirectionToPoint(airplane.getPosition(), sf::Vector2f(assetsManager->getResolution().width/2, assetsManager->getResolution().height/2));
}

void Airplane::render(sf::RenderTarget *window)
{
    window->draw(airplane);

    if (isInControlArea == true && isSelected == true)
    {
        window->draw(callsign);
        window->draw(altitude.second);
        window->draw(airspeed.second);
    }
}

void Airplane::update(sf::Vector2i mousePosition)
{
    this->mousePosition = mousePosition;

    if(radarMovement.getElapsedTime().asMilliseconds() >= 700)
    {
        airplane.move(sf::Vector2f(
			sin((heading + 0) * PI / 180) * velocity,
			cos((heading + 180) * PI / 180) * velocity
		));

        if (controlArea.isInArea(airplane.getPosition()) && isInControlArea == false)
        {
            isInControlArea = true;
        }

        // UPDATING TEXT POSITION

        sf::Vector2f airplanePosition = airplane.getPosition();

        callsign.setPosition(airplanePosition.x, airplanePosition.y - 50);
        altitude.second.setPosition(airplanePosition.x, airplanePosition.y - 35);
        airspeed.second.setPosition(airplanePosition.x, airplanePosition.y - 20);

		
		radarMovement.restart();
    }
}

void Airplane::processEvents(sf::Event event)
{
    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (airplane.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)) == true)
                {
                    if (isInControlArea == true)
                    {
                        isSelected = true;
                    }
                }
                else
                {
                    isSelected = false;
                }
            }

            break;
        }
        default:
            break;
    }
}

void Airplane::initShapes()
{
    airplane.setSize(sf::Vector2f(8, 8));
    airplane.setFillColor(sf::Color::Transparent);
    airplane.setOutlineColor(sf::Color::White);
    airplane.setOutlineThickness(2);
}

void Airplane::initData()
{
    std::vector<std::string> list_Callsign = { "KLM", "ROT", "WZZ", "TAP", "UAE", "BAW" };

    callsign.setString(list_Callsign[rand() % list_Callsign.size()] + std::to_string(rand() % 9999));

    altitude.first = rand() % (39000 - 5000) + 5000;
    altitude.first -= altitude.first % 100;
    altitude.second.setString(std::to_string(altitude.first));

    airspeed.first = (altitude.first / 100) + 80;
    airspeed.second.setString(std::to_string(airspeed.first));


    callsign.setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
    callsign.setCharacterSize(12);

    altitude.second.setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
    altitude.second.setCharacterSize(12);
   
    airspeed.second.setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
    airspeed.second.setCharacterSize(12);
}
