#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "AppWindow.hpp"
#include "RegionButton.hpp"

#define NUMBER_OF_REGIONS 10

class Menu : public AppWindow {
public:
    Menu();


private:
    void checkHovers();
    void internalHandleEvent(const std::optional<sf::Event>& event) override;
    void internalRender() override;
    void internalUpdate() override;

private:
    sf::Texture m_texture;
    sf::Sprite m_background;

    sf::Text liveData;
    sf::Text localData;

    std::vector<RegionButton> m_buttons;
    std::vector<sf::Texture> m_flagTextures;

    bool m_liveApi = true;
};