#include "../header/Airplane.h"
#include "../header/Math.h"

//-----------------------------------------------------------
// Purpose: Used for specific updates
// Obs: FlyingEntity::update() is the general purpose update function
//-----------------------------------------------------------
void Airplane::internalUpdate() {
    const sf::Vector2f translationToPoint = Math::TranslatePositionToPoint(static_cast<float>(m_speed),
                                                                           static_cast<float>(m_heading));
    m_entity.move(translationToPoint);
}