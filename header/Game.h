//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

#include "Window.h"
#include "Airplane.h"
#include "ResourcesManager.h"
#include "DataAPI.h"
#include "Airport.h"

class Game : public Window {
public:
    explicit Game(ResourcesManager *resourcesManager);
    ~Game() { std::cout<<"Destr Game\n"; };

private:
    void render() override;
    void handleEvent() override;
    void update() override;

    void addNewEntities();
    void initAirports();

    std::vector<Airplane> m_airplanes;
    std::vector<Airport> m_airports;

    ResourcesManager *m_resourcesManager;
    DataAPI m_dataApi;

    sf::Clock m_newEntities_interval;

    sf::Texture t;
    sf::Sprite aprt;
};


#endif //OOP_GAME_H
