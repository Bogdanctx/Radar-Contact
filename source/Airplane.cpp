//
// Created by bgd on 11.04.2024.
//

#include "../header/Airplane.h"
#include "../header/Math.h"

void Airplane::internalUpdate() {
    const sf::Vector2f translationToPoint = Math::TranslatePositionToPoint(static_cast<float>(m_speed),
                                                                           static_cast<float>(m_heading));
    m_entity.move(translationToPoint);
}