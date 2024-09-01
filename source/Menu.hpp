#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "AppWindow.hpp"

class Menu : public AppWindow {
public:
    Menu();


private:
    void checkHovers();
    void internalHandleEvent(const sf::Event& event) override;
    void internalRender() override;
    void internalUpdate() override;


    class Button
    {
    public:
        void init(const std::string& regionName, float x, float y);
        const std::string& getName() const;
        sf::RectangleShape& getButton();
        const sf::Text& getLabel() const;

    private:
        std::string m_regionName;
        sf::Text m_label;
        sf::Texture m_texture;
        sf::RectangleShape m_rectangle;
    };

private:
    sf::Texture m_texture;
    sf::Sprite m_background;

    sf::Text liveData;
    sf::Text localData;

    std::array<Button, 10> m_buttons;

    bool m_liveApi = true;
};