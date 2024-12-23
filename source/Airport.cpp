#include "Airport.hpp"
#include "ResourcesManager.hpp"

Airport::Airport(sf::Vector2f position, const std::string &airportICAO) :
                m_coverage(16),
                m_labelICAO(ResourcesManager::Instance().getFont("Raleway-Regular.ttf"), airportICAO, 8)
{
    sf::FloatRect bounds = m_coverage.getGlobalBounds();

    m_coverage.setOrigin(bounds.position + bounds.size / 2.f); // maybe should cast to int
    m_coverage.setFillColor(sf::Color(255, 223, 135, 100)); // yellow-ish color
    m_coverage.setPosition(sf::Vector2f(static_cast<int>(position.x),static_cast<int>(position.y))); // cast to fix blurry text

    bounds = m_labelICAO.getGlobalBounds();
    m_labelICAO.setOrigin(bounds.position + bounds.size / 2.f);
    m_labelICAO.setPosition(sf::Vector2f(static_cast<int>(position.x), static_cast<int>(position.y))); // cast to fix blurry text
}

void Airport::render(sf::RenderWindow *window) const
{
    window->draw(m_coverage);
    window->draw(m_labelICAO);
}

std::string Airport::getIcao() const
{
    return m_labelICAO.getString();
}

sf::FloatRect Airport::getBounds() const
{
    return m_coverage.getGlobalBounds();
}
