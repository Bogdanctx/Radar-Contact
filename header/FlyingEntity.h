//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_FLYINGENTITY_H
#define OOP_FLYINGENTITY_H

#include <SFML/Graphics.hpp>

#include "ResourcesManager.h"

class FlyingEntity {
public:
    FlyingEntity(int altitude, int speed, int heading, const std::string &squawk,
                          const std::string &callsign, sf::Vector2f position, const std::string &arrival);
    ~FlyingEntity() = default;

    virtual void update();
    virtual void render(sf::RenderWindow *game_window);
    virtual void handleEvent(sf::Event game_event, sf::Vector2f mouse_position);

    sf::Vector2f getEntityPosition() const;
    int getAltitude() const;
    int getAirspeed() const;

    void setDanger(int conflictType);
    void setCrashed();
    bool getCrashed() const;
    std::string getCallsign() const;
    std::string getArrival() const;

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
    sf::Text m_arrivalText{};

    sf::RectangleShape m_headingStick{};

    void updateText(const sf::Vector2f &position);
    void checkAltitudeChange();
    void checkSpeedChange();
    void checkHeadingChange();

private:
    bool m_isCrashed{};
    std::string m_callsign{};
    std::string m_arrival;

    int m_updateInterval{};
};


#endif //OOP_FLYINGENTITY_H
