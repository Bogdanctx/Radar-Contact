#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "FlyingEntity.hpp"

class Airport {
public:
    Airport(sf::Vector2f position, const std::string &airportICAO);

    void render(sf::RenderWindow *window) const;

    bool isFlyingEntityInside(const std::shared_ptr<FlyingEntity> &flyingEntity) const;

private:
    sf::CircleShape m_coverage;
    sf::Text m_labelICAO;
};
