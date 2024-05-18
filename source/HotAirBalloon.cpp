//
// Created by bgd on 22.04.2024.
//

#include "../header/HotAirBalloon.h"
#include "../header/Math.h"

void HotAirBalloon::internalUpdate() {
    const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);
    m_entity.move(translation_to_point);

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        m_headingStick.setRotation((float)m_heading - 90);
    }
}

void HotAirBalloon::render(sf::RenderWindow *game_window) {
    game_window->draw(m_entity);
    game_window->draw(m_callsignText);

    if(m_entitySelected)
    {
        game_window->draw(m_arrivalText);
        game_window->draw(m_headingText);
        game_window->draw(m_speedText);
        game_window->draw(m_altitudeText);
        game_window->draw(m_squawkText);

        game_window->draw(m_newSpeedText);
        game_window->draw(m_newAltitudeText);
        game_window->draw(m_newHeadingText);
        game_window->draw(m_headingStick);
    }
}