//
// Created by bgd on 14.06.2024.
//

#include "../header/AirplaneInfo.h"

AirplaneInfo::AirplaneInfo(const std::string& strFormat, std::shared_ptr<FlyingEntity>& flyingEntity, int offset) :
                            m_body(sf::Vector2f(230, 20)),
                            flyingEntityPtr(flyingEntity)

{
    m_body.setFillColor(sf::Color(27, 28, 27, 110));
    m_body.setOutlineColor(sf::Color::White);
    m_body.setOutlineThickness(1.2f);
    m_body.setPosition(0, (float)offset * 20);

    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(10);
    m_text.setString(strFormat);
    m_text.setPosition(5, (float)offset * 20 + 4);
    m_text.setFont(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"));
}

void AirplaneInfo::draw(sf::RenderWindow *window) {
    window->draw(m_body);
    window->draw(m_text);
}