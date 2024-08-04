#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "FlyingEntity.hpp"
#include "FlightInfo.hpp"

class FlightsTable {
public:
    FlightsTable();

    void render(sf::RenderWindow *window) const;
    void update(std::vector<std::shared_ptr<FlyingEntity>> &flyingEntities);
    void handleEvent(const sf::Event& gameEvent, sf::Vector2f mousePosition);

private:
    sf::Font m_poppins;

    std::vector<FlightInfo> m_airplanesInfo{};
};
