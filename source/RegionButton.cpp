#include "RegionButton.hpp"
#include "ResourcesManager.hpp"

void RegionButton::init(const std::string& regionName, float x, float y)
{
    m_regionName = regionName;
    m_rectangle.setSize(sf::Vector2f(50, 30));
    m_rectangle.setOutlineThickness(2.3f);

    m_texture.loadFromFile("./resources/flags/" + regionName + ".png");

    m_label.setFont(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"));
    m_label.setCharacterSize(12);

    m_rectangle.setTexture(&m_texture);
    m_rectangle.setPosition(x, y);

    if(regionName == "UK") {
        m_label.setString("UK & Ireland");
        x = x - 10;
    }
    else if(regionName == "Spain") {
        m_label.setString("Spain & Portugal");
        x = x - 25;
    }
    else {
        m_label.setString(regionName);
    }

    m_label.setPosition(x, y + 30);
}

void RegionButton::setOutlineColor(const sf::Color color)
{
    m_rectangle.setOutlineColor(color);
}


const std::string& RegionButton::getName() const
{
    return m_regionName;
}

sf::RectangleShape RegionButton::getButton() const
{
    return m_rectangle;
}

const sf::Text& RegionButton::getLabel() const
{
    return m_label;
}