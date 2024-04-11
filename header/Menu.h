//
// Created by bgd on 09.04.2024.
//

#ifndef OOP_MENU_H
#define OOP_MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Window.h"
#include "ResourcesManager.h"

class Menu : public Window {
public:
    explicit Menu(ResourcesManager *resourcesManager);
    ~Menu();
private:
    void render() override;
    void handleEvent() override;
    void update() override;

    void checkHovers();

    sf::Texture m_texture;
    sf::Sprite m_background;
    std::vector<sf::RectangleShape> m_buttons;
    const std::vector<std::pair<int, int>> m_available_resolutions;
    const int m_numberOfButtons;
    ResourcesManager *m_resourcesManager;
};


#endif //OOP_MENU_H
