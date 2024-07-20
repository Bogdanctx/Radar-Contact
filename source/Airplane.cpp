#include "../header/Airplane.h"
#include "../header/Math.h"

void Airplane::internalUpdate() {
    const sf::Vector2f translationToPoint = Math::TranslatePositionToPoint(static_cast<float>(m_speed),
                                                                           static_cast<float>(m_heading));
    m_entity.move(translationToPoint);
}

void Airplane::hijackUpdateData() {
    setNewHeading(Utilities::randGen<int>(0, 360));
    setNewSpeed(Utilities::randGen<int>(160, 335));
    setNewAltitude(Utilities::randGen<int>(2000, 43000) / 100 * 100);
}