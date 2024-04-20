//
// Created by bgd on 20.04.2024.
//

#include "../header/Helicopter.h"
#include "../header/Math.h"

Helicopter::Helicopter(int altitude, int speed, int heading, const std::string &squawk, const std::string &callsign,
                       sf::Vector2f position, const std::string &arrival) :
        FlyingEntity(altitude, speed, heading, squawk, callsign, position, arrival),
        m_updateInterval{600},
        m_updateAltitudeInterval{750},
        m_updateSpeedInterval{680},
        m_updateHeadingInterval{70}
{

}

void Helicopter::update() {
    updateFlightData();

    if(m_updatePositionInterval.getElapsedTime().asMilliseconds() >= m_updateInterval)
    {
        if(m_heading == m_newHeading) {
            const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);

            m_entity.move(translation_to_point);

            updateText(m_entity.getPosition());

        }
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            m_headingStick.setRotation((float)m_heading - 90);
        }

        m_updatePositionInterval.restart();
    }
}

void Helicopter::updateFlightData() {
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