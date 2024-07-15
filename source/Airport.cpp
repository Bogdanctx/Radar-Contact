//
// Created by bgd on 12.04.2024.
//

#include "../header/Airport.h"

Airport::Airport(sf::Vector2f position, const std::string &airportICAO) :
                m_coverage(16),
                m_labelICAO{airportICAO, ResourcesManager::Instance().getFont("Raleway-Regular.ttf"), 8}
{
    sf::FloatRect bounds = m_coverage.getGlobalBounds();

    m_coverage.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    m_coverage.setFillColor(sf::Color(255, 223, 135, 100));
    m_coverage.setPosition(static_cast<int>(position.x), static_cast<int>(position.y));

    bounds = m_labelICAO.getGlobalBounds();
    m_labelICAO.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    m_labelICAO.setPosition(static_cast<int>(position.x), static_cast<int>(position.y));
}

void swap(Airport& airport1, Airport& airport2) {
    std::swap(airport1.m_coverage, airport2.m_coverage);
    std::swap(airport1.m_labelICAO, airport2.m_labelICAO);
}

void Airport::render(sf::RenderWindow *window) {
    window->draw(m_coverage);
    window->draw(m_labelICAO);
}

bool Airport::isFlyingEntityInside(const std::shared_ptr<FlyingEntity> &flyingEntity) {

    if(flyingEntity->getArrival() == m_labelICAO.getString())
    {
        sf::FloatRect bounds = m_coverage.getGlobalBounds();

        return flyingEntity->getAltitude() <= 10000 && flyingEntity->getAirspeed() <= 250 &&
                bounds.contains(flyingEntity->getEntityPosition());
    }

    return false;
}