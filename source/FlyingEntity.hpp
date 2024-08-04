#pragma once

#include <SFML/Graphics.hpp>

#include <utility>
#include <memory>
#include <deque>
#include <array>

#include "utils.hpp"
#include "Waypoint.hpp"
#include "OneDecimalFloatingPoint.h"

class FlyingEntity {
protected:
    struct Clocks {
        Clocks() = default;
        explicit Clocks(int update, int altitude = 0, int speed = 0, int heading = 0) : m_updateInterval(update),
                                                                m_altitudeInterval(altitude),
                                                                m_speedInterval(speed),
                                                                m_headingInterval(heading) {}

        sf::Clock m_altitudeClock;
        sf::Clock m_speedClock;
        sf::Clock m_headingClock;
        sf::Clock m_updateClock;

        int m_updateInterval{};
        int m_altitudeInterval{};
        int m_speedInterval{};
        int m_headingInterval{};
    };
public:
    enum Flags {
        CLEAR,
        WARNING_COLLISION,
        DANGER_COLLISION,
        LOW_FUEL,
        LOST_COMMS,
        HIJACK,
        GENERAL_EMERGENCY,
        LENGTH
    };

public:
    FlyingEntity(int altitude, int speed, int heading, const std::string &squawk, const std::string &callsign,
                 sf::Vector2f position, const std::string &arrival);
    virtual ~FlyingEntity() = default;

    void update();
    void updateText();
    void updateCursorPosition(sf::Vector2f position);

    virtual void render(sf::RenderWindow *gameWindow);
    virtual void handleEvent(const sf::Event& gameEvent, sf::Vector2f mousePosition);

    sf::Vector2f getEntityPosition() const;
    int getAltitude() const;
    int getAirspeed() const;

    std::pair<sf::Clock, int> getUpdateClock() const;

    void setCrashed();
    void setEntitySelected();
    bool getIsEntitySelected() const;
    void addWaypointToRoute(const Waypoint& waypoint);
    Waypoint getRouteCurrentWaypoint() const;
    bool getCrashed() const;
    bool isInsideScreen() const;
    const std::string& getArrival() const;
    const std::string& getCallsign() const;

    void setFallInWeather(int degree);
    void setFlag(Flags flag);
    void resetFlag(Flags flag);
    bool isFlagActive(Flags flag) const;

protected:
    void updateAltitudeData();
    void updateSpeedData();
    void updateHeadingData();

    virtual void checkAltitudeChange();
    virtual void checkSpeedChange();
    virtual void checkHeadingChange();

    virtual void internalUpdate() = 0;
    virtual void hijackUpdateData();

    void setClocks(Clocks clocks);

    // these functions set actual flying entities' data
    void setHeading(int heading);
    void setAltitude(int altitude);
    void setSpeed(int speed);
    //////////

    // these functions will change the value of the blue textx
    void setNewHeading(int newHeading);
    void setNewAltitude(int newAltitude);
    void setNewSpeed(int newSpeed);
    ///////////////////////////

protected:
    std::array<bool, Flags::LENGTH> m_flags{};

    std::deque<Waypoint> route;
    sf::RectangleShape m_entity;
    bool m_entitySelected;
    sf::Text m_callsignText;

    int m_heading;
    int m_speed;
    int m_altitude;
    OneDecimalFloatingPoint m_fuel;

    int m_newHeading;
    int m_newAltitude;
    int m_newSpeed;

    int m_minSpeed{}, m_maxSpeed{};
    int m_minAltitude{}, m_maxAltitude{};
private:
    void updateFuel();
    void updateEntityColor();
    void adjustFlightParametersBasedOnWeather();
    void handleSpecialFlightConditions();

private:
    friend class FlyingEntity_Decorator;

    sf::Vector2f m_mousePosition;

    int m_fallInWeather;

    bool m_isCrashed;
    Clocks m_clocks;

    sf::Clock m_hijackChangesClock;
    int m_hijackChangesInterval{};

    sf::Clock m_lostCommsClock;
    int m_lostCommsInterval{};

    sf::Clock m_fuelConsumptionClock;
    double m_fuelConsumptionInterval;
    bool hasFuel;

    std::string m_arrival;
    sf::Text m_arrivalText;

    std::string m_squawk;
    sf::Text m_squawkText;

    sf::Text m_routeWaypointsText;
    std::string m_routeWaypoints;

    sf::Text m_headingText;
    sf::Text m_speedText;
    sf::Text m_altitudeText;
    sf::Text m_fuelText;

    sf::Text m_newHeadingText;
    sf::Text m_newSpeedText;
    sf::Text m_newAltitudeText;

    std::string m_callsign;

    sf::RectangleShape m_headingStick;
};

class FlyingEntity_Decorator {
public:
    static std::string toText(const std::shared_ptr<FlyingEntity>& component) {
        const std::string callsign = component->m_callsign;
        const std::string altitude = component->m_altitudeText.getString() + "ft";
        const std::string airspeed = component->m_speedText.getString() + "kts";
        const std::string arrival = component->m_arrival;
        const std::string waypointName = component->getRouteCurrentWaypoint().getName();

        const std::string result = callsign + "     " + altitude + "     " + airspeed + "     " + arrival + "     " + waypointName;

        return result;
    }
};
