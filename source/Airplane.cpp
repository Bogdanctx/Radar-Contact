//
// Created by bgd on 11.04.2024.
//

#include "../header/Airplane.h"
#include "../header/Math.h"

Airplane::Airplane(int altitude, int speed, int heading, const std::string& squawk,
                   const std::string &callsign, sf::Vector2f position) :
        FlyingEntity(altitude, speed, heading, squawk, callsign, position),
        m_updateInterval{900},
        m_updateAltitudeInterval{970}
{

}

void Airplane::update() {
    checkAltitudeChange();

    if(m_updatePositionInterval.getElapsedTime().asMilliseconds() >= m_updateInterval)
    {
        const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);
        m_entity.move(translation_to_point);

        updateText(m_entity.getPosition());

        m_updatePositionInterval.restart();
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && m_altitude != m_newAltitde && m_updateAltitudeClock.getElapsedTime().asMilliseconds() >= m_updateAltitudeInterval)
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