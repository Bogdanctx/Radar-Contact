//
// Created by bgd on 28.04.2024.
//

#include "../header/Satellite.h"
#include "../header/Math.h"

void Satellite::render(sf::RenderWindow *game_window) {
    game_window->draw(m_entity);
    for(int i = 0; i < 6; i++) {
        game_window->draw(body[i]);
    }
}

void Satellite::update() {
    if(m_updatePositionInterval.getElapsedTime().asMilliseconds() >= m_updateInterval)
    {
        const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed,
                                                                                 (float) m_heading);

        m_entity.move(translation_to_point);
        for(int i = 0; i < 6; i++) {
            body[i].move(translation_to_point);
        }

        updateText(m_entity.getPosition());

        m_updatePositionInterval.restart();
    }
}