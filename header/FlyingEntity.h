//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_FLYINGENTITY_H
#define OOP_FLYINGENTITY_H

#include <SFML/Graphics.hpp>

#include <utility>

class FlyingEntity {
public:
    FlyingEntity() = default;
    FlyingEntity(int altitude, int speed, int heading, const std::string &squawk,
                          const std::string &callsign, sf::Vector2f position, const std::string &arrival);
    virtual FlyingEntity* clone() const = 0;
    virtual ~FlyingEntity() = default;

    virtual void update() = 0;
    virtual void render(sf::RenderWindow *game_window) = 0;
    virtual void handleEvent(sf::Event game_event, sf::Vector2f mouse_position);

    friend void swap(FlyingEntity &flyingEntity1, FlyingEntity& flyingEntity2);

    sf::Vector2f getEntityPosition() const;
    int getAltitude() const;
    int getAirspeed() const;

    void setDanger(int conflictType);
    void setCrashed();
    bool getCrashed() const;
    std::string getCallsign() const;
    std::string getArrival() const;

protected:
    FlyingEntity(const FlyingEntity &other) = default;
    FlyingEntity& operator=(const FlyingEntity& other) = default;

    int m_heading{};
    int m_speed{};
    int m_altitude{};
    std::string m_squawk{};
    sf::RectangleShape m_entity{};
    int m_newHeading{};
    int m_newAltitde{};
    int m_newSpeed{};
    bool m_entitySelected{};

    sf::Text m_headingText{};
    sf::Text m_speedText{};
    sf::Text m_altitudeText{};
    sf::Text m_squawkText{};
    sf::Text m_callsignText{};
    sf::Text m_arrivalText{};

    sf::Text m_newHeadingText{};
    sf::Text m_newSpeedText{};
    sf::Text m_newAltitudeText{};

    sf::RectangleShape m_headingStick{};

    void updateAltitudeData(int updateTime);
    void updateSpeedData(int updateTime);
    void updateHeadingData(int updateTime);
    void updateText(const sf::Vector2f &position);

    virtual void checkAltitudeChange();
    virtual void checkSpeedChange();
    virtual void checkHeadingChange();
private:
    sf::Vector2f m_mousePosition;

    sf::Clock m_updateAltitudeClock{};
    sf::Clock m_updateSpeedClock{};
    sf::Clock m_updateHeadingClock{};

    bool m_isCrashed{};
    std::string m_callsign{};
    std::string m_arrival;
};


#endif //OOP_FLYINGENTITY_H
