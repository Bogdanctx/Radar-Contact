//
// Created by bgd on 11.04.2024.
//

#include "../header/FlyingEntity.h"
#include "../header/Math.h"

FlyingEntity::FlyingEntity(int altitude, int speed, int heading, const std::string &squawk,
                           const std::string &callsign, sf::Vector2f position, const std::string &arrival) :
        m_heading{heading}, m_speed{speed},
        m_altitude{altitude}, m_squawk{squawk},
        m_newHeading{heading}, m_newAltitde{altitude},
        m_newSpeed{speed},
        m_entitySelected{false},
        m_headingText{std::to_string(heading), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_newHeadingText{std::to_string(m_newHeading), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_speedText{std::to_string(speed), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},

        m_newSpeedText{std::to_string(speed), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_altitudeText{std::to_string(altitude), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_newAltitudeText{std::to_string(altitude), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_squawkText(squawk, ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10),
        m_callsignText{callsign, ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_arrivalText{arrival, ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},

        m_headingStick{sf::Vector2f(26, 1.2f)},
        m_callsign{callsign},
        m_arrival{arrival},
        m_updateInterval{800}
{
    m_entity.setSize(sf::Vector2f(10, 10));
    m_entity.setFillColor(sf::Color::White);
    m_entity.setOrigin(sf::Vector2f(5, 5)); // pun originea in mijloc
    m_entity.setPosition(position);

    m_newAltitudeText.setFillColor(sf::Color::Cyan);
    m_newSpeedText.setFillColor(sf::Color::Cyan);
    m_newHeadingText.setFillColor(sf::Color::Cyan);

    m_headingStick.setFillColor(sf::Color::Cyan);
    m_headingStick.setPosition(position);
    m_headingStick.setSize(sf::Vector2f(26, 1.2));
    m_headingStick.setRotation((float)heading - 90);

    updateText(position);
}

void FlyingEntity::update()
{
    if(m_updatePositionInterval.getElapsedTime().asMilliseconds() >= m_updateInterval)
    {
        const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);
        m_entity.move(translation_to_point);

        updateText(m_entity.getPosition());

        m_updatePositionInterval.restart();
    }
}

void FlyingEntity::render(sf::RenderWindow *game_window)
{
    game_window->draw(m_entity);
    game_window->draw(m_callsignText);

    if(m_entitySelected)
    {
        game_window->draw(m_arrivalText);
        game_window->draw(m_headingText);
        game_window->draw(m_speedText);
        game_window->draw(m_altitudeText);
        game_window->draw(m_squawkText);

        game_window->draw(m_newSpeedText);
        game_window->draw(m_newAltitudeText);
        game_window->draw(m_newHeadingText);
        game_window->draw(m_headingStick);
    }
}

void FlyingEntity::updateText(const sf::Vector2f &position) {
    if(m_entitySelected) {
        int xOffset;

        m_callsignText.setPosition(position.x - 8, position.y - 30);

        xOffset = (int) position.x - 8 + m_callsignText.getLocalBounds().width + 5;
        m_squawkText.setPosition((float)xOffset, position.y - 30);
        xOffset += (int) m_squawkText.getLocalBounds().width + 5;
        m_arrivalText.setPosition((float)xOffset, position.y - 30);

        xOffset = (int) position.x - 8;
        m_speedText.setPosition((float)xOffset, position.y - 20);

        xOffset += (int) m_speedText.getLocalBounds().width + 5;
        m_headingText.setPosition((float)xOffset, position.y - 20);

        xOffset += (int)m_headingText.getLocalBounds().width + 5;
        m_altitudeText.setPosition((float)xOffset, position.y - 20);

        xOffset += (int) m_altitudeText.getLocalBounds().width + 5;
        m_newSpeedText.setPosition((float)xOffset, position.y - 20);

        xOffset += (int) m_newSpeedText.getLocalBounds().width + 5;
        m_newHeadingText.setPosition((float)xOffset, position.y - 20);

        xOffset += (int) m_newHeadingText.getLocalBounds().width + 5;
        m_newAltitudeText.setPosition((float) xOffset, position.y - 20);

        m_headingStick.setPosition(position.x, position.y);
    }
    else {
        m_callsignText.setPosition(position.x - 5, position.y - 20);
    }
}

void FlyingEntity::handleEvent(const sf::Event game_event, const sf::Vector2f mouse_position)
{
    if(m_entitySelected)
    {
        checkAltitudeChange();
        checkSpeedChange();
        checkHeadingChange();
    }

    m_mousePosition = mouse_position;

    switch(game_event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            sf::FloatRect entity_bounds = m_entity.getGlobalBounds();

            if(entity_bounds.contains(mouse_position))
            {
                m_entitySelected = true;
                updateText(m_entity.getPosition());
            }
            else
            {
                m_entitySelected = false;
                updateText(m_entity.getPosition());
            }
        }

        default:
            break;
    }
}

void FlyingEntity::checkAltitudeChange() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            m_newAltitde += 1000;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            m_newAltitde -= 1000;
        }

        if(m_newAltitde != m_altitude) {
            m_newAltitudeText.setString(std::to_string(m_newAltitde));
        }
    }
}

void FlyingEntity::checkSpeedChange() {
    if(sf::Keyboard::isKeyPressed((sf::Keyboard::LAlt)))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            m_newSpeed++;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            m_newSpeed--;
        }

        if(m_newSpeed != m_speed) {
            m_newSpeedText.setString(std::to_string(m_newSpeed));
        }
    }
}

void FlyingEntity::checkHeadingChange() {
    if(sf::Keyboard::isKeyPressed((sf::Keyboard::LShift))) {
        m_newHeading = Math::DirectionToPoint(m_entity.getPosition(), m_mousePosition);
        m_newHeadingText.setString(std::to_string(m_newHeading));
        m_headingStick.setRotation((float) m_newHeading - 90);

        if (m_newSpeed != m_speed) {
            m_newSpeedText.setString(std::to_string(m_newSpeed));
        }
    }
}

void FlyingEntity::setDanger(const int conflictType) {
    if(conflictType == 0) { // nu exista conflict
        m_entity.setFillColor(sf::Color::White);
    }
    else if(conflictType == 1) { // entitatile se aproprie una de cealalta
        m_entity.setFillColor(sf::Color(230, 140, 44));
    }
    else if(conflictType == 2) { // coliziunea este iminenta
        m_entity.setFillColor(sf::Color::Red);
    }
}

void FlyingEntity::setCrashed() {
    m_isCrashed = true;
}

bool FlyingEntity::getCrashed() const {
    return m_isCrashed;
}

std::string FlyingEntity::getCallsign() const {
    return m_callsign;
}

int FlyingEntity::getAltitude() const {
    return m_altitude;
}

sf::Vector2f FlyingEntity::getEntityPosition() const {
    return m_entity.getPosition();
}

std::string FlyingEntity::getArrival() const {
    return m_arrival;
}