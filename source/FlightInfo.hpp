#ifndef OOP_FLIGHTINFO_H
#define OOP_FLIGHTINFO_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "FlyingEntity.hpp"
#include "ResourcesManager.hpp"

class FlightInfo {
public:
    FlightInfo(const std::string& strFormat, std::shared_ptr<FlyingEntity>& flyingEntity, int offset);

    void draw(sf::RenderWindow* window);

    std::shared_ptr<FlyingEntity> getFlyingEntityPtr() const;
    sf::RectangleShape getBody() const;

private:
    sf::RectangleShape m_body;
    sf::Text m_text;
    std::string m_info;
    std::shared_ptr<FlyingEntity> flyingEntityPtr;
};


#endif //OOP_FLIGHTINFO_H
