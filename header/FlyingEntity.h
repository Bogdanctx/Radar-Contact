//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_FLYINGENTITY_H
#define OOP_FLYINGENTITY_H

#include <SFML/Graphics.hpp>

#include <utility>
#include <memory>

class FlyingEntity {
protected:
    struct Clocks {
        Clocks() = default;
        explicit Clocks(int update, int altitude = 0, int speed = 0, int heading = 0) : m_updateInterval(update),
                                                                m_altitudeInterval(altitude),
                                                                m_speedInterval(speed),
                                                                m_headingInterval(heading) {}

        sf::Clock m_altitudeClock{};
        sf::Clock m_speedClock{};
        sf::Clock m_headingClock{};
        sf::Clock m_updateClock{};

        int m_updateInterval{};
        int m_altitudeInterval{};
        int m_speedInterval{};
        int m_headingInterval{};
    };

public:
    FlyingEntity() = default;
    FlyingEntity(int altitude, int speed, int heading, const std::string &squawk,
                          const std::string &callsign, sf::Vector2f position, const std::string &arrival);
    virtual FlyingEntity* clone() const = 0;
    virtual ~FlyingEntity() = default;

    void update(bool force = false);
    virtual void render(sf::RenderWindow *game_window) = 0;
    virtual void handleEvent(sf::Event game_event, sf::Vector2f mouse_position);

    friend void swap(FlyingEntity &flyingEntity1, FlyingEntity& flyingEntity2);

    sf::Vector2f getEntityPosition() const;
    int getAltitude() const;
    int getAirspeed() const;

    void setDanger(int conflictType);
    void setCrashed();
    void setEntitySelected();
    bool getCrashed() const;
    bool isInsideScreen() const;
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
    int m_newAltitude{};
    int m_newSpeed{};
    bool m_entitySelected{};

    int m_minSpeed{}, m_maxSpeed{};
    int m_minAltitude{}, m_maxAltitude{};

    sf::Text m_headingText{};
    sf::Text m_speedText{};
    sf::Text m_altitudeText{};
    sf::Text m_squawkText{};
    sf::Text m_callsignText{};
    sf::Text m_arrivalText{};

    sf::Text m_newHeadingText{};
    sf::Text m_newSpeedText{};
    sf::Text m_newAltitudeText{};

    std::string m_callsign{};

    sf::RectangleShape m_headingStick{};

    void updateAltitudeData();
    void updateSpeedData();
    void updateHeadingData();
    void updateText(const sf::Vector2f &position);

    virtual void checkAltitudeChange();
    virtual void checkSpeedChange();
    virtual void checkHeadingChange();

    void setAltitudeConstraints(int minAltitude, int maxAltitude);
    void setSpeedConstraints(int minSpeed, int maxSpeed);
    void setClocks(Clocks clock);
private:
    virtual void internalUpdate() = 0;

    friend class FlyingEntity_Decorator;

    Clocks m_clocks{};

    sf::Vector2f m_mousePosition;

    bool m_isCrashed{};
    std::string m_arrival;
};

class FlyingEntity_Decorator {
public:
    FlyingEntity_Decorator() = delete;
    explicit FlyingEntity_Decorator(std::shared_ptr<FlyingEntity> component) : m_component(std::move(component)) {}

    std::string to_text() {
        const std::string callsign = m_component->m_callsign;
        const std::string altitude = m_component->m_altitudeText.getString() + "ft";
        const std::string airspeed = m_component->m_speedText.getString() + "kts";
        const std::string arrival = m_component->m_arrival;

        const std::string result = callsign + "     " + altitude + "     " + airspeed + "     " + arrival;

        return result;
    }
private:
    std::shared_ptr<FlyingEntity> m_component{};
};

#endif //OOP_FLYINGENTITY_H
