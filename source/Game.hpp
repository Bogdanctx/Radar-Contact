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
#include "Region.hpp"
#include "LiveAPI.hpp"
#include "MockAPI.hpp"

class Game : public AppWindow {
public:
    Game() = delete;
    Game(const std::string &selectedRegion, bool usingLiveAPI);

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

    nlohmann::json fetchNewFlyingEntities();

    void removeCrashedEntities();

private:
    nlohmann::json m_downloadedFlyingEntities;
    nlohmann::json m_incomingFlyingEntities;
    int m_usedDownloadedData = 0;

    std::vector<Airport> m_airports;
    std::vector<std::shared_ptr<FlyingEntity>> m_flyingEntities;
    std::unordered_set<std::string> m_fetchedFlyingEntities;

    sf::Clock m_updateWeatherClock;
    sf::Clock m_newEntitiesInterval;
    sf::Clock m_flightTableClock;
    sf::Clock m_loadingScreenDelay;
    sf::Sprite m_backgroundRegion;
    sf::Sound m_atcSound;

    Weather weather;
    FlightsTable flightsTable;
    Region m_region;
    std::shared_ptr<LiveAPI> m_api;

    std::vector<Waypoint> m_waypoints;

    bool m_renderFlightsTable = true;
    bool m_renderWaypoints = true;
};
