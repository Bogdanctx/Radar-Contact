#include "Helicopter.hpp"
#include "Math.hpp"

//-----------------------------------------------------------
// Purpose: Used for specific updates
// Obs: FlyingEntity::update() is the general purpose update function
//-----------------------------------------------------------
void Helicopter::internalUpdate() {
    if(m_heading == m_newHeading) {
        const sf::Vector2f translationToPoint = Math::TranslatePositionToPoint(static_cast<float>(m_speed),
                                                                    static_cast<float>(m_heading));
        m_entity.move(translationToPoint);
    }
}