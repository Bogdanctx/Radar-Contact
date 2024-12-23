#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "FlyingEntity.hpp"
#include "FlightInfo.hpp"

class FlightsTable {
public:
    FlightsTable();

    void render(sf::RenderWindow *window) const;
    void update(const std::list<std::shared_ptr<FlyingEntity>> &flyingEntities);
    void handleEvent(const std::optional<sf::Event>& event, sf::Vector2f mousePosition);

private:
    sf::Font m_poppins{};

    std::list<FlightInfo> m_airplanesInfo{};
};
