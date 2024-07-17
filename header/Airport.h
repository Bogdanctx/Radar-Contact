#ifndef OOP_AIRPORT_H
#define OOP_AIRPORT_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

#include "ResourcesManager.h"
#include "FlyingEntity.h"

class Airport {
public:
    Airport(sf::Vector2f position, const std::string &airportICAO);

    void render(sf::RenderWindow *window);

    bool isFlyingEntityInside(const std::shared_ptr<FlyingEntity> &flyingEntity);

private:
    sf::CircleShape m_coverage;
    sf::Text m_labelICAO;
};


#endif //OOP_AIRPORT_H
