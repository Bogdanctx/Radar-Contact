//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_MENU_H
#define OOP_MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "ResourcesManager.h"
#include "Window.h"

class Menu : public Window {
public:
    Menu();
    ~Menu() = default;
private:
    void render() override;
    void handleEvent() override;
    void update() override;

    void checkHovers();

    sf::Texture m_texture;
    sf::Sprite m_background;

    std::vector<std::pair<sf::RectangleShape, std::string>> m_regionsButtons;
};


#endif //OOP_MENU_H
