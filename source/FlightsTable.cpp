#include "FlightsTable.hpp"

FlightsTable::FlightsTable() : m_poppins(ResourcesManager::Instance().getFont("Poppins-Regular.ttf")) {}

void FlightsTable::draw(sf::RenderWindow *window) {
    for(FlightInfo& airplaneInfo: m_airplanesInfo) {
        airplaneInfo.draw(window);
    }
}

//-----------------------------------------------------------
// Purpose: Update the top-left table with flying entities
//-----------------------------------------------------------
void FlightsTable::update(std::vector<std::shared_ptr<FlyingEntity>> &flyingEntities) {
    m_airplanesInfo.clear();

    for(auto &flyingEntity: flyingEntities) {
        FlightInfo info(FlyingEntity_Decorator::toText(flyingEntity), flyingEntity, static_cast<int>(m_airplanesInfo.size()));

        m_airplanesInfo.emplace_back(info);
    }
}

void FlightsTable::handleEvent(const sf::Event& gameEvent, sf::Vector2f mousePosition) {
    switch(gameEvent.type) {
        case sf::Event::MouseButtonPressed: {
            for(auto &airplaneInfo: m_airplanesInfo) {
                if(airplaneInfo.getBody().getGlobalBounds().contains(mousePosition)) {
                    airplaneInfo.getFlyingEntityPtr()->setEntitySelected();
                }
            }

            break;
        }
        default:
            break;
    }
}



