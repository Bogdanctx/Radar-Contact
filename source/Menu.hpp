#pragma once

#include <SFML/Graphics.hpp>

#include <array>

#include "Window.hpp"

class Menu : public Window {
public:
    Menu();
private:
    void render() override;
    void handleEvent() override;
    void update() override;

    void checkHovers();

private:
    sf::Texture m_texture;
    sf::Sprite m_background;

    sf::Text liveData;
    sf::Text localData;

    std::array<std::pair<sf::RectangleShape, std::string>, 10> m_regionsButtons;
    std::array<sf::Texture, 10> m_flagsTexture;
    std::array<sf::Text, 10> m_flagsLabel;
};