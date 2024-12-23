#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>
#include <memory>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "AppWindow.hpp"
#include "Airport.hpp"
#include "Weather.hpp"
#include "FlightsTable.hpp"
#include "Region.hpp"
#include "LiveAPI.hpp"
#include "utils.hpp"

class Game : public AppWindow {
public:
    Game() = delete;
    Game(const std::string &selectedRegion, bool usingLiveAPI);

private:
    void internalRender() override;
    void internalHandleEvent(const std::optional<sf::Event>& event) override;
    void internalUpdate() override;

    void loadElements();
    void loadWaypoints();
    void setLoadingScreen(const std::future<void>& future);

    void addNewEntities();

    void initAirports();
    void checkForEntitiesCollisions();
    void checkInsideAirspace() const;
    void checkInsideWeather();

    nlohmann::json fetchNewFlyingEntities();

    void removeCrashedEntities();

private:
    nlohmann::json m_downloadedFlyingEntities;
    nlohmann::json m_incomingFlyingEntities;
    int m_usedDownloadedData = 0;

    std::list<Waypoint> m_waypoints;
    std::list<Airport> m_airports;
    std::list<std::shared_ptr<FlyingEntity>> m_flyingEntities;
    std::unordered_set<std::string> m_fetchedFlyingEntities;

    bool weatherThreadLaunched = false;
    bool airtrafficThreadLaunched = false;

    Utility::Timer m_updateWeatherClock{5 * 60 * 1000}; // 5 minutes
    Utility::Timer m_newEntitiesInterval{6 * 60 * 1000}; // 6 minutes
    Utility::Timer m_flightTableClock{3000};

    sf::Sound m_atcSound;
    sf::SoundBuffer m_atcSoundBuffer;

    Weather weather;
    FlightsTable flightsTable;
    Region m_region;
    std::shared_ptr<LiveAPI> m_api;

    bool m_renderFlightsTable = true;
    bool m_renderWaypoints = true;
};
