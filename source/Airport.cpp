//
// Created by bgd on 12.04.2024.
//

#include "../header/Airport.h"

Airport::Airport(sf::Vector2f position, const std::string airportICAO) : m_coverage(15)
{
    m_coverage.setFillColor(sf::Color(255, 223, 135, 100));
    m_coverage.setPosition(position);
}

void Airport::render(sf::RenderWindow *window) {
    window->draw(m_coverage);
}