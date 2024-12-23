#include "FlightsTable.hpp"
#include "ResourcesManager.hpp"

FlightsTable::FlightsTable() : m_poppins(ResourcesManager::Instance().getFont("Poppins-Regular.ttf")) {}

void FlightsTable::render(sf::RenderWindow *window) const {
    for(const FlightInfo& airplaneInfo: m_airplanesInfo) {
        airplaneInfo.render(window);
    }
}

//-----------------------------------------------------------
// Purpose: Update the top-left table with flying entities
//-----------------------------------------------------------
void FlightsTable::update(const std::list<std::shared_ptr<FlyingEntity>> &flyingEntities) {
    m_airplanesInfo.clear();

    for(const std::shared_ptr<FlyingEntity> &flyingEntity: flyingEntities) {
        FlightInfo info(FlyingEntity_Decorator::toText(flyingEntity), flyingEntity, static_cast<int>(m_airplanesInfo.size()));

        m_airplanesInfo.push_back(info);
    }
}

void FlightsTable::handleEvent(const std::optional<sf::Event>& event, const sf::Vector2f mousePosition)
{

    if(event->is<sf::Event::MouseButtonPressed>())
    {
        for(const FlightInfo &airplaneInfo: m_airplanesInfo)
        {
            if(airplaneInfo.getBody().getGlobalBounds().contains(mousePosition))
            {
                airplaneInfo.getFlyingEntityPtr()->setEntitySelected();
            }
        }
    }


}



