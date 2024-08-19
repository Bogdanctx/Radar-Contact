#pragma once

#include <SFML/Graphics.hpp>

class Airport {
public:
    Airport(sf::Vector2f position, const std::string &airportICAO);

    void render(sf::RenderWindow *window) const;

    std::string getIcao() const;
    sf::FloatRect getBounds() const;

private:
    sf::CircleShape m_coverage;
    sf::Text m_labelICAO;
};
