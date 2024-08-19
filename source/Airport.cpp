#include "Airport.hpp"
#include "ResourcesManager.hpp"

Airport::Airport(sf::Vector2f position, const std::string &airportICAO) :
                m_coverage(16),
                m_labelICAO{airportICAO, ResourcesManager::Instance().getFont("Raleway-Regular.ttf"), 8}
{
    sf::FloatRect bounds = m_coverage.getGlobalBounds();

    m_coverage.setOrigin(static_cast<int>(bounds.left + bounds.width / 2.f), // cast to fix blurry text
                         static_cast<int>(bounds.top + bounds.height / 2.f));

    m_coverage.setFillColor(sf::Color(255, 223, 135, 100)); // yellow-ish color

    m_coverage.setPosition(static_cast<int>(position.x),static_cast<int>(position.y)); // cast to fix blurry text

    bounds = m_labelICAO.getGlobalBounds();
    m_labelICAO.setOrigin(static_cast<int>(bounds.left + bounds.width / 2.f), // cast to fix blurry text
                          static_cast<int>(bounds.top + bounds.height / 2.f));

    m_labelICAO.setPosition(static_cast<int>(position.x), static_cast<int>(position.y)); // cast to fix blurry text
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
