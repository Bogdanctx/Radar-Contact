//
// Created by bgd on 20.04.2024.
//

#include "../header/Helicopter.h"
#include "../header/Math.h"

void Helicopter::internalUpdate() {
    if(m_heading == m_newHeading) {
        const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed,
                                                                                 (float) m_heading);
        m_entity.move(translation_to_point);
    }
}