//
// Created by bgd on 12.04.2024.
//

#include "../header/Airport.h"

Airport::Airport(sf::Vector2f position, const std::string &airportICAO) :
                m_coverage(16),
                m_labelICAO{airportICAO, ResourcesManager::Instance().getFont("Raleway-Regular.ttf"), 8}
{
    m_coverage.setOrigin(8, 8);
    m_coverage.setFillColor(sf::Color(255, 223, 135, 100));
    m_coverage.setPosition(position);

    m_labelICAO.setPosition(position);
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