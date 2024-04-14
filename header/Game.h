//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <nlohmann/json.hpp>
#include <unordered_set>

#include "Window.h"
#include "Airplane.h"
#include "ResourcesManager.h"
#include "Airport.h"
#include "Weather.h"

class Game : public Window {
public:
    explicit Game(ResourcesManager &resourcesManager);
    ~Game() = default;

    void run() override;
private:
    void render() override;
    void handleEvent() override;
    void update() override;

    void addNewEntities();
    void initAirports();

    std::vector<Airplane> m_airplanes;
    std::vector<Airport> m_airports;

    ResourcesManager m_resourcesManager;

    sf::Clock m_newEntitiesInterval;
    sf::Sprite m_backgroundRegion;
    sf::Text m_connectingToFrequency;

    std::unordered_set<std::string> m_addedEntities;
    const std::string m_selectedRegion = "UK";

    bool m_isFirstTime;

    Weather weather;
};


#endif //OOP_GAME_H
