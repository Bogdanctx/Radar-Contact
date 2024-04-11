//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_FLYINGENTITY_H
#define OOP_FLYINGENTITY_H

#include <SFML/Graphics.hpp>

#include "Math.h"

class FlyingEntity {
public:
    FlyingEntity(int altitude, int max_altitude, int speed, int max_speed, int heading, int tcas, sf::Vector2f position);

    virtual void update();
    virtual void render(sf::RenderWindow *game_window);
protected:
    int m_heading{};
    int m_speed{};
    int m_altitude{};
    int m_tcas{};
private:

    sf::RectangleShape m_entity{};
    sf::Vector2f m_position{};

    const int m_max_altitude{};
    const int m_max_speed{};
    const std::string m_callsign;

    const int m_update_interval = 500;

    sf::Clock m_update_position_interval; // la un interval x de timp se va actualiza pozitia avionului
};


#endif //OOP_FLYINGENTITY_H
