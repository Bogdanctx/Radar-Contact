//
// Created by bgd on 12.04.2024.
//

#ifndef OOP_AIRPORT_H
#define OOP_AIRPORT_H

#include <SFML/Graphics.hpp>

#include "ResourcesManager.h"
#include "FlyingEntity.h"

class Airport {
public:
    explicit Airport(sf::Vector2f position, const std::string &airportICAO);
    ~Airport() = default;

    void render(sf::RenderWindow *window);

    bool isFlyingEntityInside(FlyingEntity *flyingEntity);

private:
    sf::CircleShape m_coverage{};
    sf::Text m_labelICAO{};
};


#endif //OOP_AIRPORT_H
