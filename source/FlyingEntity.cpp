//
// Created by bgd on 11.04.2024.
//

#include "../header/FlyingEntity.h"
#include "../header/Math.h"

FlyingEntity::FlyingEntity(int altitude, int speed, int heading, const std::string &squawk,
                           const std::string &callsign, sf::Vector2f position) :
        m_heading{heading},
        m_speed{speed},
        m_altitude{altitude},
        m_squawk{squawk},
        m_callsign{callsign},
        m_updateInterval{800},
        m_entitySelected{false},

        m_headingText{std::to_string(heading), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_speedText{std::to_string(speed), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_altitudeText{std::to_string(altitude), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_squawkText(squawk, ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10),
        m_callsignText{callsign, ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10}
{
    m_entity.setSize(sf::Vector2f(10, 10));
    m_entity.setFillColor(sf::Color::White);

    m_entity.setOrigin(sf::Vector2f(5, 5)); // pun originea in mijloc

    m_entity.setPosition(position);

    updateText(position);
}

void FlyingEntity::update()
{
    if(m_updatePositionInterval.getElapsedTime().asMilliseconds() >= m_updateInterval)
    {
        const sf::Vector2f translation_to_point = Math::TranslatePositionToPoint((float) m_speed, (float) m_heading);
        m_entity.move(translation_to_point);

        updateText(m_entity.getPosition());

        m_updatePositionInterval.restart();
    }
}

void FlyingEntity::render(sf::RenderWindow *game_window)
{
    game_window->draw(m_entity);
    game_window->draw(m_callsignText);

    if(m_entitySelected)
    {
        game_window->draw(m_headingText);
        game_window->draw(m_speedText);
        game_window->draw(m_altitudeText);
        game_window->draw(m_squawkText);
    }
}

void FlyingEntity::updateText(const sf::Vector2f &position) {
    if(m_entitySelected) {
        int xOffset = (int) position.x - 8;
        m_speedText.setPosition((float)xOffset, position.y - 20);
        xOffset += (int) m_speedText.getLocalBounds().width + 5;
        m_headingText.setPosition((float)xOffset, position.y - 20);
        xOffset += (int)m_headingText.getLocalBounds().width + 5;
        m_altitudeText.setPosition((float)xOffset, position.y - 20);

        m_callsignText.setPosition(position.x - 8, position.y - 30);
        m_squawkText.setPosition(position.x - 8 + m_callsignText.getLocalBounds().width + 5, position.y - 30);
    }
    else {
        m_callsignText.setPosition(position.x - 5, position.y - 20);
    }
}

void FlyingEntity::handleEvent(const sf::Event game_event, const sf::Vector2f mouse_position)
{
    switch(game_event.type)
    {
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