#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>
#include <utility>
#include <typeinfo>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "Window.h"
#include "Airplane.h"
#include "Helicopter.h"
#include "Airport.h"
#include "HotAirBalloon.h"
#include "Weather.h"
#include "FlightsTable.h"

class Game : public Window {
public:
    Game();

private:
    void render() override;
    void handleEvent() override;
    void update() override;

    void loadElements();
    void loadWaypoints();

    void addNewBalloons();
    void addNewEntities();

    void initAirports();
    void checkForEntitiesCollisions();
    void checkInsideAirspace();
    void checkOutsideScreen();
    void checkInsideWeather();

    void removeCrashedEntities();

    std::vector<Airport> m_airports{};
    std::vector<std::shared_ptr<FlyingEntity>> m_flyingEntities{};
    std::unordered_set<std::string> m_fetchedFlyingEntities;

    sf::Clock m_updateWeatherClock{};
    sf::Clock m_newEntitiesInterval{};
    sf::Clock m_flightTableClock{};
    sf::Clock m_loadingScreenDelay{};
    sf::Sprite m_backgroundRegion{};
    sf::Sound m_atcSound{};

    Weather weather{};
    FlightsTable flightsTable{};

    std::vector<Waypoint> m_waypoints{};

    bool m_renderFlightsTable{};
    bool m_renderWaypoints{};
};


#endif //OOP_GAME_H
