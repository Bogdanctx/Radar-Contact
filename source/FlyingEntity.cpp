//
// Created by bgd on 11.04.2024.
//

#include "../header/FlyingEntity.h"

FlyingEntity::FlyingEntity(int altitude, int max_altitude, int speed, int max_speed, int heading, int tcas, sf::Vector2f position):
    m_heading(heading), m_speed(speed), m_altitude(altitude), m_tcas{tcas},
    m_position{position}, m_max_altitude(max_altitude), m_max_speed(max_speed)
{
    m_entity.setSize(sf::Vector2f(10, 10));
    m_entity.setPosition(position);
    m_entity.setFillColor(sf::Color::White);

    sf::FloatRect entity_bounds = m_entity.getGlobalBounds();
    m_entity.setOrigin(sf::Vector2f(entity_bounds.left + 5, entity_bounds.top + 5)); // pun originea in mijloc

}

void FlyingEntity::update()
{
    if(m_update_position_interval.getElapsedTime().asMilliseconds() >= m_update_interval)
    {
        const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);
        m_entity.move(translation_to_point);

        m_update_position_interval.restart();
    }
}

void FlyingEntity::render(sf::RenderWindow *game_window)
{
    game_window->draw(m_entity);
}