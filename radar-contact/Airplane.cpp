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
    newHeading.first = std::get<0>(heading) = Math::DirectionToPoint(airplane.getPosition(), sf::Vector2f(assetsManager->getResolution().width/2, assetsManager->getResolution().height/2));

    std::get<1>(heading).setString(std::to_string((short)std::get<0>(heading)));
}

void Airplane::render(sf::RenderTarget *window)
{
    window->draw(airplane);

    if (isInControlArea == true && isSelected == true)
    {
        window->draw(callsign);
        window->draw(altitude.second);
        window->draw(airspeed.second);
        window->draw(std::get<1>(heading));
        window->draw(std::get<2>(heading));


        if (settingNewData)
        {
            window->draw(newAirspeed.second);
            window->draw(newAltitude.second);
            window->draw(newHeading.second);
        }

    }
}

void Airplane::update(sf::Vector2i mousePosition)
{
    this->mousePosition = mousePosition;

    HandleAltitudeChange();
    HandleAirspeedChange();
    HandleHeadingChange();

    UpdateData();

    if(radarMovement.getElapsedTime().asMilliseconds() >= 700)
    {
        airplane.move(sf::Vector2f(
			sin((std::get<0>(heading) + 0) * PI / 180) * velocity,
			cos((std::get<0>(heading) + 180) * PI / 180) * velocity
		));

        if (controlArea.isInArea(airplane.getPosition()) && isInControlArea == false)
        {
            isInControlArea = true;
        }

        // UPDATING TEXT POSITION

        sf::Vector2f airplanePosition = airplane.getPosition();

        callsign.setPosition(airplanePosition.x, airplanePosition.y - 50.f);
        altitude.second.setPosition(airplanePosition.x, airplanePosition.y - 35.f);
        airspeed.second.setPosition(airplanePosition.x, airplanePosition.y - 20.f);

        newAltitude.second.setPosition(airplanePosition.x + altitude.second.getGlobalBounds().width + 5.f, airplanePosition.y - 35.f);
        newAirspeed.second.setPosition(airplanePosition.x + airspeed.second.getGlobalBounds().width + 5.f, airplanePosition.y - 20.f);

        std::get<2>(heading).setPosition(airplanePosition.x+4.f, airplanePosition.y+4.f);
        std::get<1>(heading).setPosition(airplanePosition.x + callsign.getGlobalBounds().width + 3.5f, airplanePosition.y - 50.f);
		
        sf::FloatRect headingGlobalBounds = std::get<1>(heading).getGlobalBounds();

        newHeading.second.setPosition(airplanePosition.x + headingGlobalBounds.left + headingGlobalBounds.width + 3.5f, airplanePosition.y - 50.f);

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

    std::get<2>(heading).setSize(sf::Vector2f(2, 30));
    std::get<2>(heading).setFillColor(sf::Color::Cyan);
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

    newAirspeed.first = airspeed.first;
    newAltitude.first = altitude.first;

    callsign.setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
    callsign.setCharacterSize(12);

    altitude.second.setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
    altitude.second.setCharacterSize(12);
   
    airspeed.second.setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
    airspeed.second.setCharacterSize(12);
    
    newAltitude.second.setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
    newAltitude.second.setCharacterSize(12);
    newAltitude.second.setFillColor(sf::Color::Cyan);
    newAltitude.second.setString(std::to_string(newAltitude.first));

    newAirspeed.second.setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
    newAirspeed.second.setCharacterSize(12);
    newAirspeed.second.setFillColor(sf::Color::Cyan);
    newAirspeed.second.setString(std::to_string(newAirspeed.first));

    std::get<1>(heading).setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
    std::get<1>(heading).setCharacterSize(12);

    newHeading.second.setFont(assetsManager->getFont("MerriweatherSans-Regular.ttf"));
    newHeading.second.setCharacterSize(12);


}

void Airplane::UpdateData()
{
    if (airspeed.first != newAirspeed.first && airspeedChanged.getElapsedTime().asMilliseconds() >= 600 && settingNewData == false)
    {
        if (airspeed.first < newAirspeed.first)
        {
            airspeed.first++;
            airspeed.second.setString(std::to_string(airspeed.first));
        }
        if (airspeed.first > newAirspeed.first)
        {
            airspeed.first--;
            airspeed.second.setString(std::to_string(airspeed.first));
        }

        airspeedChanged.restart();
    }
    if (altitude.first != newAltitude.first && altitudeChanged.getElapsedTime().asMilliseconds() >= 700 && settingNewData == false)
    {
        if (altitude.first < newAltitude.first)
        {
            altitude.first += 100;
            altitude.second.setString(std::to_string(altitude.first));
        }
        if (altitude.first > newAltitude.first)
        {
            altitude.first -= 100;
            altitude.second.setString(std::to_string(altitude.first));
        }

        altitudeChanged.restart();
    }
    if (std::get<0>(heading) != newHeading.first && settingNewData == false)
    {
        std::get<0>(heading) = newHeading.first;
        std::get<1>(heading).setString(std::to_string((short)newHeading.first));
        std::get<2>(heading).setRotation(newHeading.first - 180);

        std::get<1>(heading).setFillColor(sf::Color::White);
    }
}

void Airplane::HandleAltitudeChange()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) == true)
    {
        settingNewData = true;

        if (dataUpdate.getElapsedTime().asMilliseconds() >= 100)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                newAltitude.first += 100;

                newAltitude.second.setString(std::to_string(newAltitude.first));

                dataUpdate.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                newAltitude.first -= 100;

                newAltitude.second.setString(std::to_string(newAltitude.first));

                dataUpdate.restart();
            }
        }

    }
    else
    {
        settingNewData = false;
    }
}

void Airplane::HandleAirspeedChange()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) == true)
    {
        settingNewData = true;

        if (dataUpdate.getElapsedTime().asMilliseconds() >= 100)
        {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                newAirspeed.first++;

                newAirspeed.second.setString(std::to_string(newAirspeed.first));

                dataUpdate.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                newAirspeed.first++;

                newAirspeed.second.setString(std::to_string(newAirspeed.first));

                dataUpdate.restart();
            }

        }
    }
    else
    {
        settingNewData = false;
    }
}

void Airplane::HandleHeadingChange()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true)
    {
        short x1, x2;
        short y1, y2;

        x1 = airplane.getPosition().x;
        x2 = mousePosition.x;
        y1 = airplane.getPosition().y;
        y2 = mousePosition.y;

        newHeading.first = -atan2(x2 - x1, y2 - y1) * 180 / PI;

        if (newHeading.first < 0)
            newHeading.first += 360;

        std::get<1>(heading).setString(std::to_string((short)newHeading.first));
        std::get<2>(heading).setRotation(newHeading.first - 180.f);

        std::get<1>(heading).setFillColor(sf::Color::Cyan);

        settingNewData = true;
    }
    else
    {
        settingNewData = false;
    }
}