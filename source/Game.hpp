#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "AppWindow.hpp"
#include "Airport.hpp"
#include "Weather.hpp"
#include "FlightsTable.hpp"

class Game : public AppWindow {
public:
    Game();

private:
    void render() override;
    void handleEvent() override;
    void update() override;

    void loadElements();
    void loadWaypoints();

    void addNewEntities();

    void initAirports();
    void checkForEntitiesCollisions();
    void checkInsideAirspace();
    void checkInsideWeather();

    void removeCrashedEntities();

private:
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

    int m_totalFetchedEntities = 0;

    bool m_renderFlightsTable{};
    bool m_renderWaypoints{};
};
