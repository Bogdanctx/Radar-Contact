//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_FLYINGENTITY_H
#define OOP_FLYINGENTITY_H

#include <SFML/Graphics.hpp>

#include "ResourcesManager.h"

class FlyingEntity {
public:
    explicit FlyingEntity(int altitude, int speed, int heading, const std::string &squawk,
                          const std::string &callsign, sf::Vector2f position);
    ~FlyingEntity() = default;

    virtual void update();
    virtual void render(sf::RenderWindow *game_window);
    virtual void handleEvent(sf::Event game_event, sf::Vector2f mouse_position);
protected:
    int m_heading{};
    int m_speed{};
    int m_altitude{};
    std::string m_squawk{};
    sf::RectangleShape m_entity{};
    sf::Clock m_updatePositionInterval{}; // la un interval x de timp se va actualiza pozitia avionului


    void updateText(const sf::Vector2f &position);
private:
    const std::string m_callsign{};

    const int m_updateInterval{};
    bool m_entitySelected{};

    sf::Text m_headingText{};
    sf::Text m_speedText{};
    sf::Text m_altitudeText{};
    sf::Text m_squawkText{};
    sf::Text m_callsignText{};
};


#endif //OOP_FLYINGENTITY_H
