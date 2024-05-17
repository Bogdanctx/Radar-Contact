//
// Created by bgd on 17.05.2024.
//

#ifndef OOP_FLIGHTSTABLE_H
#define OOP_FLIGHTSTABLE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "FlyingEntity.h"
#include "ResourcesManager.h"

class FlightsTable {
public:
    FlightsTable();

    void draw(sf::RenderWindow *window);
    void update(std::vector<std::shared_ptr<FlyingEntity>> &flyingEntities);
    void handleEvent(sf::Event gameEvent, sf::Vector2f mousePosition);

private:
    sf::Font m_poppins{};

    struct AirplaneInfo {
        AirplaneInfo() : m_body(sf::Vector2f(230, 20)) {

            m_body.setFillColor(sf::Color(27, 28, 27, 110));
            m_body.setOutlineColor(sf::Color::White);
            m_body.setOutlineThickness(1.2f);

            m_text.setFillColor(sf::Color::White);
            m_text.setCharacterSize(10);
        }

        sf::RectangleShape m_body{};
        sf::Text m_text;
        std::string m_info{};
        std::shared_ptr<FlyingEntity> flyingEntityPtr{};
    };

    std::vector<AirplaneInfo> m_airplanesInfo{};
};


#endif //OOP_FLIGHTSTABLE_H
