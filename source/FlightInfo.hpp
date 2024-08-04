#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "FlyingEntity.hpp"

class FlightInfo {
public:
    FlightInfo(const std::string& strFormat, const std::shared_ptr<FlyingEntity>& flyingEntity, int offset);

    void render(sf::RenderWindow* window) const;

    std::shared_ptr<FlyingEntity> getFlyingEntityPtr() const;
    sf::RectangleShape getBody() const;

private:
    sf::RectangleShape m_body;
    sf::Text m_text;
    std::string m_info;
    std::shared_ptr<FlyingEntity> flyingEntityPtr;
};
