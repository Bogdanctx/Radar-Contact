//
// Created by bgd on 12.04.2024.
//

#ifndef OOP_AIRPORT_H
#define OOP_AIRPORT_H

#include <SFML/Graphics.hpp>

#include "ResourcesManager.h"
#include "DataAPI.h"

class Airport {
public:
    explicit Airport(sf::Vector2f position, const std::string &airportICAO);
    ~Airport() = default;

    void render(sf::RenderWindow *window);
    void handleEvent(sf::Event event, sf::Vector2f mousePosition);

    std::string getIcao() const { return m_labelICAO.getString(); }

private:
    bool m_isCoverageSelected{};
    //std::pair<int, int> m_weather{}; // (direction, wind)

    std::pair<int, int> m_windData{};
    sf::CircleShape m_coverage{};
    sf::Text m_labelICAO{};
    sf::Text m_windDataText{};
};


#endif //OOP_AIRPORT_H
