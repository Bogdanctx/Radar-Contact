//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "Window.h"
#include "Airplane.h"
#include "Helicopter.h"
#include "Airport.h"
#include "HotAirBalloon.h"
#include "Weather.h"
#include "DataAPI.h"

class Game : public Window {
public:
    Game();

    void run() override;
private:
    void render() override;
    void handleEvent() override;
    void update() override;

    void addNewBalloons();
    void addNewEntities();
    void initAirports();
    void checkForEntitiesCollisions();
    void checkInsideAirspace();

    void removeCrashedEntities();

    std::vector<Airport> m_airports{};
    std::vector<std::shared_ptr<FlyingEntity>> m_flyingEntities;


    sf::Clock m_updateWeatherClock{};
    sf::Clock m_newEntitiesInterval{};
    sf::Sprite m_backgroundRegion{};
    sf::Sound m_atcSound{};

    const std::string m_selectedRegion{};

    Weather weather{};
    DataAPI dataAPI{};
};


#endif //OOP_GAME_H
