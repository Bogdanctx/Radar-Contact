//
// Created by bgd on 11.04.2024.
//

#include "../header/Airplane.h"
#include "../header/Math.h"

Airplane::Airplane(int altitude, int speed, int heading, const std::string& squawk,
                   const std::string &callsign, sf::Vector2f position) :
        FlyingEntity(altitude, speed, heading, squawk, callsign, position),
        m_updateInterval{900}
{

}

void Airplane::update() {
    if(m_updatePositionInterval.getElapsedTime().asMilliseconds() >= m_updateInterval)
    {
        const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);
        m_entity.move(translation_to_point);

        updateText(m_entity.getPosition());

        m_updatePositionInterval.restart();
    }
}