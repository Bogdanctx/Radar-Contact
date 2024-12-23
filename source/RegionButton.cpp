#include "RegionButton.hpp"
#include "ResourcesManager.hpp"

RegionButton::RegionButton(const std::string& regionName, float x, float y, const sf::Texture* texture) :
        m_regionName(regionName),
        m_label(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), regionName, 12),
        m_rectangle(sf::Vector2f(50, 30))
{
    m_rectangle.setOutlineThickness(2.3f);
    m_rectangle.setTexture(texture, true);
    m_rectangle.setPosition(sf::Vector2f(x, y));

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

    m_label.setPosition(sf::Vector2f(x, y + 30));
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