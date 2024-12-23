#include "FlightInfo.hpp"
#include "ResourcesManager.hpp"

FlightInfo::FlightInfo(const std::string& strFormat, const std::shared_ptr<FlyingEntity>& flyingEntity, int offset) :
                            m_body(sf::Vector2f(235, 20)),
                            m_text(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), strFormat, 10),
                            flyingEntityPtr(flyingEntity)

{
    m_body.setFillColor(sf::Color(27, 28, 27, 110));
    m_body.setOutlineColor(sf::Color::White);
    m_body.setOutlineThickness(1.2f);
    m_body.setPosition(sf::Vector2f(0, offset * 20));

    m_text.setFillColor(sf::Color::White);
    m_text.setPosition(sf::Vector2f(5, offset * 20 + 5));
}

void FlightInfo::render(sf::RenderWindow *window) const {
    window->draw(m_body);
    window->draw(m_text);
}

sf::RectangleShape FlightInfo::getBody() const {
    return m_body;
}

std::shared_ptr<FlyingEntity> FlightInfo::getFlyingEntityPtr() const {
    return flyingEntityPtr;
}