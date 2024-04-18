//
// Created by bgd on 09.04.2024.
//

#include "../header/Menu.h"
Menu::Menu() :
        Window({800, 600}, "Radar Contact - Menu")
{
    m_background.setTexture(ResourcesManager::Instance().getTexture("menu.png"));
}

void Menu::render()
{
    m_window.clear();

    m_window.draw(m_background);

    m_window.display();
}

void Menu::update()
{
    checkHovers();
}

void Menu::checkHovers()
{
    // sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
    // sf::Vector2f float_mouse_position{(float) mouse_position.x, (float) mouse_position.y};


}

void Menu::handleEvent()
{
    //sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
    // sf::Vector2f float_mouse_position{(float) mouse_position.x, (float) mouse_position.y};
    sf::Event menu_event{};

    while(m_window.pollEvent(menu_event))
    {
        switch(menu_event.type)
        {
            case sf::Event::Closed: {
                m_window.close();

                break;
            }
            case sf::Event::KeyPressed:
            {
                const sf::Keyboard::Key key_code = menu_event.key.code;

                if(key_code == sf::Keyboard::Escape)
                {
                    m_window.close();
                }

                break;
            }
            case sf::Event::MouseButtonPressed:
            {


                break;
            }

            default:
                break;
        }
    }
}