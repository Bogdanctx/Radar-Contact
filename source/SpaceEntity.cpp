//
// Created by bgd on 27.04.2024.
//

#include "../header/SpaceEntity.h"
#include "../header/Math.h"

void SpaceEntity::update() {
    if(m_updatePositionInterval.getElapsedTime().asMilliseconds() >= m_updateInterval)
    {
        const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);
        m_entity.move(translation_to_point);

        updateText(m_entity.getPosition());

        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            m_headingStick.setRotation((float)m_heading - 90);
        }

        m_updatePositionInterval.restart();
    }
}

void SpaceEntity::render(sf::RenderWindow *game_window) {
    game_window->draw(m_entity);

    if(m_entitySelected)
    {
        game_window->draw(m_callsignText);
    }
}

void SpaceEntity::handleEvent(sf::Event game_event, sf::Vector2f mouse_position) {
    switch (game_event.type) {
        case sf::Event::MouseButtonPressed:
        {
            sf::FloatRect entity_bounds = m_entity.getGlobalBounds();

            if(entity_bounds.contains(mouse_position))
            {
                m_entitySelected = true;
                updateText(m_entity.getPosition());
            }
            else
            {
                m_entitySelected = false;
                updateText(m_entity.getPosition());
            }
        }
        default:
            break;
    }
}