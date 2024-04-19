//
// Created by bgd on 11.04.2024.
//

#include "../header/Airplane.h"
#include "../header/Math.h"

Airplane::Airplane(int altitude, int speed, int heading, const std::string& squawk,
                   const std::string &callsign, sf::Vector2f position) :
        FlyingEntity(altitude, speed, heading, squawk, callsign, position),
        m_updateInterval{900},
        m_updateAltitudeInterval{970},
        m_updateSpeedInterval{600},
        m_updateHeadingInterval{100}
{

}

void Airplane::update() {

    if(m_entitySelected)
    {
        checkAltitudeChange();
        checkSpeedChange();
        checkHeadingChange();
    }

    updateFlightData();

    if(m_updatePositionInterval.getElapsedTime().asMilliseconds() >= m_updateInterval)
    {
        const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);
        m_entity.move(translation_to_point);

        updateText(m_entity.getPosition());

        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            m_headingStick.setRotation((float)m_heading - 90);
        }

        m_updatePositionInterval.restart();
    }
}

void Airplane::updateFlightData() {
    bool shouldUpdateAltitude = m_updateAltitudeClock.getElapsedTime().asMilliseconds() >= m_updateAltitudeInterval;

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && m_altitude != m_newAltitde && shouldUpdateAltitude)
    {
        if(m_altitude < m_newAltitde) {
            m_altitude += 1000;
        }
        if(m_altitude > m_newAltitde) {
            m_altitude -= 1000;
        }

        m_altitudeText.setString(std::to_string(m_altitude));
        m_updateAltitudeClock.restart();
    }

    bool shouldUpdateSpeed = m_updateSpeedClock.getElapsedTime().asMilliseconds() >= m_updateSpeedInterval;

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && m_newSpeed != m_speed && shouldUpdateSpeed)
    {
        if(m_speed < m_newSpeed) {
            m_speed++;
        }
        if(m_speed > m_newSpeed) {
            m_speed--;
        }

        m_speedText.setString(std::to_string(m_speed));
        m_updateSpeedClock.restart();
    }

    bool shouldUpdateHeading = m_updateHeadingClock.getElapsedTime().asMilliseconds() >= m_updateHeadingInterval;

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
        m_updateHeadingClock.restart();
    }
}

void Airplane::checkAltitudeChange() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && m_dataChangeDelay.getElapsedTime().asMilliseconds() >= 130)
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

        m_dataChangeDelay.restart();
    }
}

void Airplane::checkSpeedChange() {
    if(sf::Keyboard::isKeyPressed((sf::Keyboard::LAlt)) && m_dataChangeDelay.getElapsedTime().asMilliseconds() >= 130)
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

        m_dataChangeDelay.restart();
    }
}

void Airplane::checkHeadingChange() {
    if(sf::Keyboard::isKeyPressed((sf::Keyboard::LShift)))
    {
        m_newHeading = Math::DirectionToPoint(m_entity.getPosition(), m_mousePosition);
        m_newHeadingText.setString(std::to_string(m_newHeading));
        m_headingStick.setRotation((float)m_newHeading - 90);

        if(m_newSpeed != m_speed) {
            m_newSpeedText.setString(std::to_string(m_newSpeed));
        }

        m_dataChangeDelay.restart();
    }
}