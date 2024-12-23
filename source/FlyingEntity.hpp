#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <deque>
#include <array>

#include "utils.hpp"
#include "Waypoint.hpp"
#include "OneDecimalFloatingPoint.h"
#include "Weather.hpp"

class FlyingEntity
{
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

    void update(sf::Vector2f mousePosition);
    void updateText();

    virtual void render(sf::RenderWindow *gameWindow);
    virtual void handleEvent(const std::optional<sf::Event>& event, sf::Vector2f mousePosition);

    sf::Vector2f getEntityPosition() const;
    int getAltitude() const;
    int getAirspeed() const;

    bool canUpdate() const;

    void setCrashed();
    void setEntitySelected();
    bool getIsEntitySelected() const;
    void addWaypointToRoute(const Waypoint& waypoint);
    Waypoint getRouteCurrentWaypoint() const;
    bool getCrashed() const;
    const std::string& getArrival() const;
    const std::string& getCallsign() const;
    OneDecimalFloatingPoint getFuel() const;

    void setFallInWeather(int degree);
    void setFlag(Flags flag);
    void resetFlag(Flags flag);
    bool isFlagActive(Flags flag) const;

protected:
    void updateAltitudeData();
    void updateSpeedData();
    void updateHeadingData();

    void checkAltitudeChange(int scrollUsed = 0);
    void checkSpeedChange(int scrollUsed = 0);
    void checkHeadingChange();

    virtual void internalUpdate() = 0;
    void hijackUpdateData();

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
    bool m_isEntitySelected = false;
    sf::Text m_callsignText;

    int m_heading{};
    int m_speed{};
    int m_altitude{};
    OneDecimalFloatingPoint m_fuel = OneDecimalFloatingPoint(Utility::randomNumber(13, 18),
                                                            Utility::randomNumber(0, 9));

    int m_newHeading{};
    int m_newAltitude{};
    int m_newSpeed{};

    int m_minSpeed{}, m_maxSpeed{};
    int m_minAltitude{}, m_maxAltitude{};

    Utility::Timer m_updateTimer;
    Utility::Timer m_speedTimer;
    Utility::Timer m_headingTimer;
    Utility::Timer m_altitudeTimer;

private:
    void updateFuel();
    void updateEntityColor();
    void adjustFlightParametersBasedOnWeather();
    void handleSpecialFlightConditions();

private:
    sf::Keyboard::Key m_altitudeButton = sf::Keyboard::Key::LAlt;
    sf::Keyboard::Key m_speedButton = sf::Keyboard::Key::LControl;
    sf::Keyboard::Key m_headingButton = sf::Keyboard::Key::LShift;

    friend class FlyingEntity_Decorator;

    sf::Vector2f m_mousePosition;

    int m_fallInWeather = Weather::RainDanger::Clear;

    bool m_isCrashed = false;

    Utility::Timer m_hijackTimer;
    Utility::Timer m_lostCommsTimer;
    Utility::Timer m_fuelConsumptionTimer{4500};
    Utility::Timer m_buttonDelayTimer{50};


    bool hasFuel = true;

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
