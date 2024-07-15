//
// Created by bgd on 20.04.2024.
//

#include "../header/Helicopter.h"
#include "../header/Math.h"

void Helicopter::internalUpdate() {
    if(m_heading == m_newHeading) {
        const sf::Vector2f translationToPoint = Math::TranslatePositionToPoint(static_cast<float>(m_speed),
                                                                                 static_cast<float>(m_heading));
        m_entity.move(translationToPoint);
    }
}