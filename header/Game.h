//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <nlohmann/json.hpp>
#include <unordered_set>
#include <future>

#include "Window.h"
#include "Airplane.h"
#include "Airport.h"
#include "Weather.h"
#include "ResourcesManager.h"
#include <typeinfo>

class Game : public Window {
public:
    Game();
    ~Game() = default;

    void run() override;
private:
    void render() override;
    void handleEvent() override;
    void update() override;

    void addNewEntities();
    void initAirports();
    void checkForEntitiesCollisions();

    std::vector<Airplane> m_airplanes{};
    std::vector<Airport> m_airports{};

    sf::Clock m_newEntitiesInterval{};
    sf::Sprite m_backgroundRegion{};

    std::unordered_set<std::string> m_addedEntities{};
    const std::string m_selectedRegion = "UK";

    bool m_isFirstTime{};

    Weather weather;
    sf::Clock m_updateWeatherClock;
};


#endif //OOP_GAME_H
