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
    int m_newHeading{};
    int m_newAltitde{};
    int m_newSpeed{};
    bool m_entitySelected{};

    sf::Vector2f m_mousePosition;

    sf::Text m_headingText{}, m_newHeadingText{};
    sf::Text m_speedText{}, m_newSpeedText{};
    sf::Text m_altitudeText{}, m_newAltitudeText{};
    sf::Text m_squawkText{};
    sf::Text m_callsignText{};

    sf::RectangleShape m_headingStick{};

    void updateText(const sf::Vector2f &position);
private:
    const std::string m_callsign{};

    const int m_updateInterval{};
};


#endif //OOP_FLYINGENTITY_H
