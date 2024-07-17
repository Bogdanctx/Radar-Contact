#ifndef OOP_WAYPOINT_H
#define OOP_WAYPOINT_H

#include <SFML/Graphics.hpp>
#include <memory>

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


#endif //OOP_WAYPOINT_H
