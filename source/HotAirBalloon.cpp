//
// Created by bgd on 22.04.2024.
//

#include "../header/HotAirBalloon.h"
#include "../header/Math.h"

void HotAirBalloon::internalUpdate() {
    const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);
    m_entity.move(translation_to_point);
}