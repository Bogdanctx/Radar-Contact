#ifndef REGIONBUTTON_HPP
#define REGIONBUTTON_HPP

#include <SFML/Graphics.hpp>

class RegionButton {
public:
    void init(const std::string& regionName, float x, float y);
    const std::string& getName() const;
    sf::RectangleShape getButton() const;
    const sf::Text& getLabel() const;

    void setOutlineColor(sf::Color color);

private:
    std::string m_regionName;
    sf::Text m_label;
    sf::Texture m_texture;
    sf::RectangleShape m_rectangle;
};

#endif //REGIONBUTTON_HPP
