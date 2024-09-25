#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "AppWindow.hpp"
#include "RegionButton.hpp"

#define NUMBER_OF_REGIONS 10

class Menu : public AppWindow {
public:
    Menu();


private:
    void checkHovers();
    void internalHandleEvent(const sf::Event& event) override;
    void internalRender() override;
    void internalUpdate() override;

private:
    sf::Texture m_texture;
    sf::Sprite m_background;

    sf::Text liveData;
    sf::Text localData;

    std::array<RegionButton, NUMBER_OF_REGIONS> m_buttons;

    bool m_liveApi = true;
};