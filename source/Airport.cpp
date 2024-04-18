//
// Created by bgd on 12.04.2024.
//

#include "../header/Airport.h"

Airport::Airport(sf::Vector2f position, const std::string airportICAO) :
                m_coverage(16), m_isCoverageSelected{false},
                m_labelICAO{airportICAO, ResourcesManager::Instance().getFont("Raleway-Regular.ttf"), 8},
                m_windDataText{"foo", ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 15}
{
    m_coverage.setOrigin(8, 8);
    m_coverage.setFillColor(sf::Color(255, 223, 135, 100));
    m_coverage.setPosition(position);

    m_labelICAO.setPosition(position);

    m_windDataText.setPosition(10, 720 - 30);
}

void Airport::render(sf::RenderWindow *window) {
    window->draw(m_coverage);
    window->draw(m_labelICAO);

    if(m_isCoverageSelected) {
        window->draw(m_windDataText);
    }
}

void Airport::handleEvent(sf::Event event, sf::Vector2f mousePosition) {

    switch(event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            sf::FloatRect coverageBounds = m_coverage.getGlobalBounds();

            if(coverageBounds.contains(mousePosition))
            {
                std::string format = m_labelICAO.getString();
                m_windData = DataAPI::getWeather(format);
                format = "WIND " + format + ' ';
                m_windDataText.setString(format + std::to_string(m_windData.first)+ "dgr " +std::to_string(m_windData.second)+"kt");
                m_isCoverageSelected = true;
            }
            else
            {
                m_isCoverageSelected = false;
            }

            break;
        }

        default:
            break;
    }

}