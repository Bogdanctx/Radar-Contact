//
// Created by bgd on 09.04.2024.
//

#include "../header/Menu.h"

Menu::Menu(std::pair<int, int> *game_resolution) : Window(500, 400, "Radar Contact - Menu"),
                m_game_resolution{game_resolution},
                m_available_resolutions{{1920, 1080}, {1600, 900}, {1280, 720}},
                m_numberOfButtons{3}
{
    const std::vector<std::pair<float, float>> buttons_position = {
            {154, 98},
            {154, 197},
            {154, 306},
    };

    for(int i = 0; i < m_numberOfButtons; i++) {
        sf::RectangleShape button;

        button.setPosition(
                sf::Vector2f(buttons_position[i].first, buttons_position[i].second)
                );
        button.setFillColor(sf::Color::Transparent);
        button.setOutlineThickness(2);
        button.setOutlineColor(sf::Color(255, 255, 255, 180));
        button.setSize(sf::Vector2f(179, 44));

        m_buttons.push_back(button);
    }

    m_texture.loadFromFile("../resources/menu/menu.png");
    m_background.setTexture(m_texture);
}

Menu::~Menu() {
    std::cout<<"Destr Menu\n";
}

void Menu::render()
{
    m_window.clear();

    m_window.draw(m_background);

    for(const auto &button: m_buttons)
    {
        m_window.draw(button);
    }

    m_window.display();
}

void Menu::update()
{
    checkHovers();
}

void Menu::checkHovers()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
    sf::Vector2f float_mouse_position{(float) mouse_position.x, (float) mouse_position.y};

    for(auto &button: m_buttons)
    {
        if(button.getGlobalBounds().contains(float_mouse_position))
        {
            button.setOutlineThickness(3.f);
            button.setOutlineColor(sf::Color::Black);
        }
        else
        {
            button.setOutlineColor(sf::Color::White);
        }
    }
}

void Menu::handleEvent()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
    sf::Vector2f float_mouse_position{(float) mouse_position.x, (float) mouse_position.y};
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
                for(int i = 0; i < m_numberOfButtons; i++) {
                    sf::FloatRect button_bounds = m_buttons[i].getGlobalBounds();

                    if(button_bounds.contains(float_mouse_position))
                    {
                        m_game_resolution->first = m_available_resolutions[i].first;
                        m_game_resolution->second = m_available_resolutions[i].second;

                        m_window.close();
                        return;
                    }
                }

                break;
            }

            default:
                break;
        }
    }
}