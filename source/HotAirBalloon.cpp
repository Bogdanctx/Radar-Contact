#include "../header/HotAirBalloon.h"
#include "../header/Math.h"

void HotAirBalloon::internalUpdate() {
    const sf::Vector2f translationToPoint = Math::TranslatePositionToPoint(static_cast<float>(m_speed),
                                                                           static_cast<float>(m_heading));
    m_entity.move(translationToPoint);
}