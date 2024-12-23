#ifndef REGIONBUTTON_HPP
#define REGIONBUTTON_HPP

#include <SFML/Graphics.hpp>

class RegionButton
{
public:
    RegionButton() : m_label(m_font) {}
    RegionButton(const std::string& regionName, float x, float y, const sf::Texture* texture);

    const std::string& getName() const;
    sf::RectangleShape getButton() const;
    const sf::Text& getLabel() const;

    void setOutlineColor(sf::Color color);
private:
    std::string m_regionName;
    sf::Texture m_texture;
    sf::Font m_font;
    sf::Text m_label;
    sf::RectangleShape m_rectangle;
};

#endif //REGIONBUTTON_HPP
