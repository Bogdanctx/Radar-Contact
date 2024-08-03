#include "Waypoint.hpp"
#include "ResourcesManager.hpp"

Waypoint::Waypoint(sf::Vector2f position, const std::string& label) :
        m_body(4, 3),
        m_label(label, ResourcesManager::Instance().getFont("Raleway-Regular.ttf"), 10)
{
    m_body.setFillColor(sf::Color::White);
    sf::FloatRect bounds = m_body.getGlobalBounds();

    m_body.setOrigin(static_cast<int>(bounds.left + bounds.width / 2.f),
                     static_cast<int>(bounds.top + bounds.height / 2.f)); // cast to fix blurry text

    m_body.setPosition(static_cast<int>(position.x), static_cast<int>(position.y));

    bounds = m_label.getGlobalBounds();
    m_label.setOrigin(static_cast<int>(bounds.left + bounds.width / 2.f), // cast to fix blurry text
                      static_cast<int>(bounds.top + bounds.height / 2.f));

    m_label.setPosition(static_cast<int>(position.x), static_cast<int>(position.y - 8));
}

sf::Vector2f Waypoint::getPosition() const {
    return m_body.getPosition();
}

sf::FloatRect Waypoint::getBounds() const {
    return m_body.getGlobalBounds();
}

void Waypoint::render(sf::RenderWindow* window) const {
    window->draw(m_body);
    window->draw(m_label);
}

std::string Waypoint::getName() const {
    return m_label.getString();
}