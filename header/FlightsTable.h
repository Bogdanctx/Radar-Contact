//
// Created by bgd on 17.05.2024.
//

#ifndef OOP_FLIGHTSTABLE_H
#define OOP_FLIGHTSTABLE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "FlyingEntity.h"
#include "ResourcesManager.h"
#include "AirplaneInfo.h"

class FlightsTable {
public:
    FlightsTable();

    void draw(sf::RenderWindow *window);
    void update(std::vector<std::shared_ptr<FlyingEntity>> &flyingEntities);
    void handleEvent(sf::Event gameEvent, sf::Vector2f mousePosition);

private:
    sf::Font m_poppins{};

    std::vector<AirplaneInfo> m_airplanesInfo{};
};

#endif //OOP_FLIGHTSTABLE_H
