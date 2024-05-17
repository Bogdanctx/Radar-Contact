//
// Created by bgd on 11.04.2024.
//

#include "../header/Airplane.h"
#include "../header/Math.h"

void Airplane::update(bool force = false) {
    updateAltitudeData(m_updateAltitudeInterval);
    updateSpeedData(m_updateSpeedInterval);
    updateHeadingData(m_updateHeadingInterval);

    if(force || m_updatePositionInterval.getElapsedTime().asMilliseconds() >= m_updateInterval)
    {
        // get next position based on speed
        const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);
        m_entity.move(translation_to_point);

        updateText(m_entity.getPosition());

        // if no direction is choosen, then heading stick might be updated
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            m_headingStick.setRotation((float)m_heading - 90);
        }

        if(!force) {
            m_updatePositionInterval.restart();
        }

    }
}

void Airplane::render(sf::RenderWindow *game_window) {
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