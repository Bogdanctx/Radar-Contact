#include "../header/FlightInfo.h"

FlightInfo::FlightInfo(const std::string& strFormat, std::shared_ptr<FlyingEntity>& flyingEntity, int offset) :
                            m_body(sf::Vector2f(235, 20)),
                            flyingEntityPtr(flyingEntity)

{
    m_body.setFillColor(sf::Color(27, 28, 27, 110));
    m_body.setOutlineColor(sf::Color::White);
    m_body.setOutlineThickness(1.2f);
    m_body.setPosition(0, offset * 20);

    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(10);
    m_text.setString(strFormat);
    m_text.setPosition(5, offset * 20 + 5);
    m_text.setFont(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"));
}

void FlightInfo::draw(sf::RenderWindow *window) {
    window->draw(m_body);
    window->draw(m_text);
}

sf::RectangleShape FlightInfo::getBody() const {
    return m_body;
}

std::shared_ptr<FlyingEntity> FlightInfo::getFlyingEntityPtr() const {
    return flyingEntityPtr;
}