//
// Created by bgd on 17.05.2024.
//

#include "../header/FlightsTable.h"

FlightsTable::FlightsTable() : m_poppins(ResourcesManager::Instance().getFont("Poppins-Regular.ttf")) {}

void FlightsTable::draw(sf::RenderWindow *window) {
    for(AirplaneInfo &airplaneInfo: m_airplanesInfo) {
        window->draw(airplaneInfo.m_body);
        window->draw(airplaneInfo.m_text);
    }
}

void FlightsTable::update(std::vector<std::shared_ptr<FlyingEntity>> &flyingEntities) {
    int size = 0;
    m_airplanesInfo.clear();

    for(auto &flyingEntity: flyingEntities) {
        AirplaneInfo info;
        FlyingEntity_Decorator flyingEntityDecorator{flyingEntity};

        info.m_text.setString(flyingEntityDecorator.to_text());
        info.m_text.setFont(m_poppins);
        info.m_text.setPosition(5, (float)size * 20 + 3);

        info.m_body.setPosition(0, (float)size * 20);

        m_airplanesInfo.emplace_back(info);

        ++size;
    }
}