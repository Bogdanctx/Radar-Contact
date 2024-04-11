//
// Created by bgd on 09.04.2024.
//

#include "../header/Game.h"

Game::Game(const int width, const int height) : Window(width, height, "Radar Contact")
{

}

void Game::update()
{

}

void Game::render()
{
    m_window.clear();

    m_window.display();
}

void Game::handleEvent()
{
    sf::Event game_event{};

    while(m_window.pollEvent(game_event))
    {
        switch(game_event.type)
        {
            case sf::Event::KeyPressed:
            {
                const sf::Keyboard::Key key_code = game_event.key.code;

                if(key_code == sf::Keyboard::Escape)
                {
                    m_window.close();
                }

                break;
            }
            case sf::Event::Closed:
            {
                m_window.close();

                break;
            }
            default:
                break;
        }
    }
}