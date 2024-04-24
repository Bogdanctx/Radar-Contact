//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include <nlohmann/json.hpp>

#include "Window.h"
#include "Airplane.h"
#include "Helicopter.h"
#include "Airport.h"
#include "HotAirBalloon.h"
#include "Weather.h"
#include "ResourcesManager.h"
#include "DataAPI.h"

class Game : public Window {
public:
    Game();
    ~Game() = default;

    void run() override;
private:
    void render() override;
    void handleEvent() override;
    void update() override;

    void addNewBalloons();
    void addNewEntities();
    void initAirports();
    static void checkForEntitiesCollisions(const std::vector<FlyingEntity*>& flyingEntities);
    void checkInsideAirspace(const std::vector<FlyingEntity*>& flyingEntities);

    void removeCrashedEntities();

    std::vector<Airplane> m_airplanes{};
    std::vector<Helicopter> m_helicopters{};
    std::vector<HotAirBalloon> m_balloons{};
    std::vector<Airport> m_airports{};

    sf::Clock m_newEntitiesInterval{};
    sf::Sprite m_backgroundRegion{};

    const std::string m_selectedRegion{};

    Weather weather{};
    DataAPI dataAPI{};

    sf::Clock m_updateWeatherClock{};
};


#endif //OOP_GAME_H
