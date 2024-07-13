//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_FLYINGENTITY_H
#define OOP_FLYINGENTITY_H

#include <SFML/Graphics.hpp>

#include <utility>
#include <memory>
#include <deque>

#include "utils.h"
#include "Waypoint.h"

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
    virtual void render(sf::RenderWindow *game_window);
    virtual void handleEvent(sf::Event game_event, sf::Vector2f mouse_position);

    sf::Vector2f getEntityPosition() const;
    int getAltitude() const;
    int getAirspeed() const;

    void setDanger(int conflictType);
    void setCrashed();
    void setEntitySelected();
    bool getIsEntitySelected() const;
    void addWaypointToRoute(const Waypoint& waypoint);
    Waypoint getRouteCurrentWaypoint() const;
    bool getCrashed() const;
    bool isInsideScreen() const;
    std::string getArrival() const;

    void setFallInWeather(int degree);

protected:
    FlyingEntity(const FlyingEntity &other) = default;
    FlyingEntity& operator=(const FlyingEntity& other) = default;

    void updateAltitudeData();
    void updateSpeedData();
    void updateHeadingData();
    void updateText(const sf::Vector2f &position);

    virtual void checkAltitudeChange();
    virtual void checkSpeedChange();
    virtual void checkHeadingChange();

    void setAltitudeConstraints(int minAltitude, int maxAltitude);
    void setSpeedConstraints(int minSpeed, int maxSpeed);

    void setClocks(Clocks clocks);

    std::deque<Waypoint> route;
    sf::RectangleShape m_entity{};
    bool m_entitySelected{};
    sf::Text m_callsignText{};

    int m_heading{};
    int m_speed{};
    int m_altitude{};

    int m_newHeading{};
    int m_newAltitude{};
    int m_newSpeed{};
private:
    virtual void internalUpdate() = 0;

    friend class FlyingEntity_Decorator;

    sf::Vector2f m_mousePosition;

    int m_fallInWeather{};

    bool m_isCrashed{};
    Clocks m_clocks{};

    std::string m_arrival{};
    sf::Text m_arrivalText{};

    std::string m_squawk{};
    sf::Text m_squawkText{};

    sf::Text m_routeWaypointsText{};
    std::string m_routeWaypoints{};

    int m_minSpeed{}, m_maxSpeed{};
    int m_minAltitude{}, m_maxAltitude{};

    sf::Text m_headingText{};
    sf::Text m_speedText{};
    sf::Text m_altitudeText{};

    sf::Text m_newHeadingText{};
    sf::Text m_newSpeedText{};
    sf::Text m_newAltitudeText{};

    std::string m_callsign{};

    sf::RectangleShape m_headingStick{};
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
        const std::string waypointName = m_component->getRouteCurrentWaypoint().getName();

        const std::string result = callsign + "     " + altitude + "     " + airspeed + "     " + arrival + "     " + waypointName;

        return result;
    }

    friend void swap(FlyingEntity_Decorator& decorator1, FlyingEntity_Decorator& decorator2) {
        using std::swap;
        swap(decorator1.m_component, decorator2.m_component);
    }
private:
    std::shared_ptr<FlyingEntity> m_component{};
};

#endif //OOP_FLYINGENTITY_H
