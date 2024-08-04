#pragma once

#include <SFML/Graphics.hpp>
class Waypoint {
public:
    Waypoint() = default;
    Waypoint(sf::Vector2f position, const std::string& label);

    sf::Vector2f getPosition() const;
    std::string getName() const;
    sf::FloatRect getBounds() const;

    void render(sf::RenderWindow* window) const;

private:
    sf::CircleShape m_body;
    sf::Text m_label;
};

