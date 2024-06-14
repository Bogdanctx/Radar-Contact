//
// Created by bgd on 17.05.2024.
//

#include "../header/FlightsTable.h"

FlightsTable::FlightsTable() : m_poppins(ResourcesManager::Instance().getFont("Poppins-Regular.ttf")) {}

void FlightsTable::draw(sf::RenderWindow *window) {
    for(AirplaneInfo& airplaneInfo: m_airplanesInfo) {
        airplaneInfo.draw(window);
    }
}

void FlightsTable::update(std::vector<std::shared_ptr<FlyingEntity>> &flyingEntities) {
    int size = 0;
    m_airplanesInfo.clear();

    for(auto &flyingEntity: flyingEntities) {
        FlyingEntity_Decorator flyingEntityDecorator{flyingEntity};

        AirplaneInfo info(flyingEntityDecorator.to_text(), flyingEntity, size);

        m_airplanesInfo.emplace_back(info);

        ++size;
    }
}

void FlightsTable::handleEvent(sf::Event gameEvent, sf::Vector2f mousePosition) {
    switch(gameEvent.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            for(auto &airplaneInfo: m_airplanesInfo) {
                if(airplaneInfo.getBody().getGlobalBounds().contains(mousePosition)) {
                    airplaneInfo.getFlyingEntityPtr()->setEntitySelected();
                    airplaneInfo.getFlyingEntityPtr()->update(true); // force update
                }
            }

            break;
        }
        default:
            break;
    }
}



