//
// Created by bgd on 28.04.2024.
//

#ifndef OOP_SATELLITE_H
#define OOP_SATELLITE_H

#include "SpaceEntity.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Satellite : public SpaceEntity {
public:
    template <typename... Args>
    explicit Satellite(Args... args) : SpaceEntity(args...) {
        sf::Vector2f startPosition = m_entity.getPosition();

        for(int i = 1; i <= 4; i++) {
            sf::RectangleShape bodyPart;

            startPosition.x -= (float)(11 - i);
            startPosition.y -= (float)(11 - i);

            bodyPart.setSize(sf::Vector2f(10, 10));
            bodyPart.setFillColor(sf::Color::White);
            bodyPart.setOrigin(sf::Vector2f(5, 5)); // set origin in middle
            bodyPart.setPosition(startPosition);

            body.push_back(bodyPart);
        }
    }

    void render(sf::RenderWindow *game_window) override;
    void update(bool force) override;

private:
    std::vector<sf::RectangleShape> body{};
};

#endif //OOP_SATELLITE_H
