//
// Created by bgd on 11.04.2024.
//

#include "../header/FlyingEntity.h"
#include "../header/Math.h"
#include "../header/ResourcesManager.h"

FlyingEntity::FlyingEntity(int altitude, int speed, int heading, const std::string &squawk,
                           const std::string &callsign, sf::Vector2f position, const std::string &arrival) :
        m_heading{heading}, m_speed{speed},
        m_altitude{altitude}, m_squawk{squawk},
        m_newHeading{heading}, m_newAltitude{altitude},
        m_newSpeed{speed},
        m_entitySelected{false},
        m_headingText{std::to_string(heading), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_speedText{std::to_string(speed), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_altitudeText{std::to_string(altitude), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},

        m_squawkText(squawk, ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10),
        m_callsignText{callsign, ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_arrivalText{arrival, ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_newHeadingText{std::to_string(m_newHeading), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_newSpeedText{std::to_string(speed), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_newAltitudeText{std::to_string(altitude), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},

        m_callsign{callsign},
        m_headingStick{sf::Vector2f(26, 1.2f)},
        m_arrival{arrival}
{
    m_entity.setSize(sf::Vector2f(10, 10));
    m_entity.setFillColor(sf::Color::White);
    m_entity.setOrigin(sf::Vector2f(5, 5)); // set origin in middle
    m_entity.setPosition(position);

    m_newAltitudeText.setFillColor(sf::Color::Cyan);
    m_newSpeedText.setFillColor(sf::Color::Cyan);
    m_newHeadingText.setFillColor(sf::Color::Cyan);

    m_headingStick.setFillColor(sf::Color::Cyan);
    m_headingStick.setPosition(position);
    m_headingStick.setSize(sf::Vector2f(26.f, 1.2f));
    m_headingStick.setRotation((float)heading - 90);

    updateText(position);
}

void FlyingEntity::updateText(const sf::Vector2f &position) {
    if(m_entitySelected) {
        float xOffset;

        m_callsignText.setPosition(position.x - 8, position.y - 30);

        xOffset = position.x - 8 + m_callsignText.getLocalBounds().width + 5;
        m_squawkText.setPosition(xOffset, position.y - 30);
        xOffset += m_squawkText.getLocalBounds().width + 5;
        m_arrivalText.setPosition(xOffset, position.y - 30);

        xOffset = position.x - 8;
        m_speedText.setPosition(xOffset, position.y - 20);

        xOffset += m_speedText.getLocalBounds().width + 5;
        m_headingText.setPosition(xOffset, position.y - 20);

        xOffset += m_headingText.getLocalBounds().width + 5;
        m_altitudeText.setPosition(xOffset, position.y - 20);

        xOffset += m_altitudeText.getLocalBounds().width + 5;
        m_newSpeedText.setPosition(xOffset, position.y - 20);

        xOffset += m_newSpeedText.getLocalBounds().width + 5;
        m_newHeadingText.setPosition(xOffset, position.y - 20);

        xOffset += m_newHeadingText.getLocalBounds().width + 5;
        m_newAltitudeText.setPosition(xOffset, position.y - 20);

        m_headingStick.setPosition(position.x, position.y);
    }
    else {
        m_callsignText.setPosition(position.x - 5, position.y - 20);
    }
}

void FlyingEntity::handleEvent(const sf::Event game_event, const sf::Vector2f mouse_position)
{
    m_mousePosition = mouse_position;

    if(m_entitySelected)
    {
        checkAltitudeChange(); // check if user changed entity altitude
        checkSpeedChange(); // check if user changed entity speed
        checkHeadingChange(); /// check if user changed entity heading
    }

    switch(game_event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            sf::FloatRect entity_bounds = m_entity.getGlobalBounds();

            // if an entity has been selected by user
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
        if(m_newAltitude + 100 <= m_maxAltitude && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            m_newAltitude += 100;
        }
        if(m_newAltitude - 100 >= m_minAltitude && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            m_newAltitude -= 100;
        }

        if(m_newAltitude != m_altitude) {
            m_newAltitudeText.setString(std::to_string(m_newAltitude));
        }
    }
}

void FlyingEntity::checkSpeedChange() {
    if(sf::Keyboard::isKeyPressed((sf::Keyboard::LAlt)))
    {
        if(m_newSpeed + 1 <= m_maxSpeed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            m_newSpeed++;
        }
        if(m_newSpeed - 1 >= m_minSpeed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            m_newSpeed--;
        }

        if(m_newSpeed != m_speed) {
            m_newSpeedText.setString(std::to_string(m_newSpeed));
        }
    }
}

void FlyingEntity::update(bool force) {
    updateAltitudeData();
    updateSpeedData();
    updateHeadingData();

    if(force || m_clocks.m_updateClock.getElapsedTime().asMilliseconds() >= m_clocks.m_updateInterval)
    {
        internalUpdate();

        updateText(m_entity.getPosition());

        if(!force) {
            m_clocks.m_updateClock.restart();
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

void FlyingEntity::setClocks(const FlyingEntity::Clocks clocks) {
    m_clocks = clocks;
}

void FlyingEntity::setAltitudeConstraints(int minAltitude, int maxAltitude) {
    m_minAltitude = minAltitude;
    m_maxAltitude = maxAltitude;
}

void FlyingEntity::setSpeedConstraints(int minSpeed, int maxSpeed) {
    m_minSpeed = minSpeed;
    m_maxSpeed = maxSpeed;
}

void FlyingEntity::setDanger(const int conflictType) {
    if(conflictType == 0) { // no conflict
        m_entity.setFillColor(sf::Color::White);
    }
    else if(conflictType == 1) { // entities are getting close to each other
        m_entity.setFillColor(sf::Color(230, 140, 44));
    }
    else if(conflictType == 2) { // collission is imminent
        m_entity.setFillColor(sf::Color::Red);
    }
}

void FlyingEntity::updateAltitudeData() {
    bool shouldUpdateAltitude = m_clocks.m_altitudeClock.getElapsedTime().asMilliseconds() >= m_clocks.m_altitudeInterval;

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && m_altitude != m_newAltitude && shouldUpdateAltitude)
    {
        if(m_altitude < m_newAltitude) {
            m_altitude += 100;
        }
        if(m_altitude > m_newAltitude) {
            m_altitude -= 100;
        }

        m_altitudeText.setString(std::to_string(m_altitude));
        m_clocks.m_altitudeClock.restart();
    }
}

void FlyingEntity::updateSpeedData() {
    bool shouldUpdateSpeed = m_clocks.m_speedClock.getElapsedTime().asMilliseconds() >= m_clocks.m_speedInterval;

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && m_newSpeed != m_speed && shouldUpdateSpeed)
    {
        if(m_speed < m_newSpeed) {
            m_speed++;
        }
        if(m_speed > m_newSpeed) {
            m_speed--;
        }

        m_speedText.setString(std::to_string(m_speed));
        m_clocks.m_speedClock.restart();
    }
}

void FlyingEntity::updateHeadingData() {
    bool shouldUpdateHeading = m_clocks.m_headingClock.getElapsedTime().asMilliseconds() >= m_clocks.m_headingInterval;

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && m_heading != m_newHeading && shouldUpdateHeading)
    {
        if ((m_newHeading - m_heading + 360) % 360 < 180) {
            m_heading++;
        } else {
            m_heading--;
        }

        if(m_heading < 0) {
            m_heading += 360;
        }
        if(m_heading >= 360) {
            m_heading -= 360;
        }

        m_headingText.setString(std::to_string(m_heading));
        m_clocks.m_headingClock.restart();
    }
}

bool FlyingEntity::isInsideScreen() const {
    sf::Vector2f position = m_entity.getPosition();

    return position.x >= -20 && position.x <= 1305 && position.y >= -20 && position.y <= 750;
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

int FlyingEntity::getAirspeed() const {
    return m_speed;
}

void FlyingEntity::setEntitySelected() {
    m_entitySelected = true;
}

void swap(FlyingEntity &flyingEntity1, FlyingEntity& flyingEntity2)
{
    std::swap(flyingEntity1.m_heading, flyingEntity2.m_heading);
    std::swap(flyingEntity1.m_speed, flyingEntity2.m_speed);
    std::swap(flyingEntity1.m_altitude, flyingEntity2.m_altitude);
    std::swap(flyingEntity1.m_squawk, flyingEntity2.m_squawk);
    std::swap(flyingEntity1.m_entity, flyingEntity2.m_entity);
    std::swap(flyingEntity1.m_newHeading, flyingEntity2.m_newHeading);
    std::swap(flyingEntity1.m_newAltitude, flyingEntity2.m_newAltitude);
    std::swap(flyingEntity1.m_newSpeed, flyingEntity2.m_newSpeed);
    std::swap(flyingEntity1.m_entitySelected, flyingEntity2.m_entitySelected);
    std::swap(flyingEntity1.m_headingText, flyingEntity2.m_headingText);
    std::swap(flyingEntity1.m_speedText, flyingEntity2.m_speedText);
    std::swap(flyingEntity1.m_altitudeText, flyingEntity2.m_altitudeText);
    std::swap(flyingEntity1.m_squawkText, flyingEntity2.m_squawkText);
    std::swap(flyingEntity1.m_callsignText, flyingEntity2.m_callsignText);
    std::swap(flyingEntity1.m_arrivalText, flyingEntity2.m_arrivalText);
    std::swap(flyingEntity1.m_newHeadingText, flyingEntity2.m_newHeadingText);
    std::swap(flyingEntity1.m_newSpeedText, flyingEntity2.m_newSpeedText);
    std::swap(flyingEntity1.m_newAltitudeText, flyingEntity2.m_newAltitudeText);
    std::swap(flyingEntity1.m_headingStick, flyingEntity2.m_headingStick);
    std::swap(flyingEntity1.m_mousePosition, flyingEntity2.m_mousePosition);
    std::swap(flyingEntity1.m_isCrashed, flyingEntity2.m_isCrashed);
    std::swap(flyingEntity1.m_callsign, flyingEntity2.m_callsign);
    std::swap(flyingEntity1.m_arrival, flyingEntity2.m_arrival);
}