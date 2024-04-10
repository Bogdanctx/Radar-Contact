//
// Created by bgd on 09.04.2024.
//

#include "../header/Game.h"

Game::Game(const int width, const int height) : m_window(sf::VideoMode(width, height), "Radar Contact") {

}

void Game::run() {
    while(m_window.isOpen())
    {

        handleEvents();
        update();
        render();

    }
}

void Game::update() {

}

void Game::render() {
    m_window.clear();

    m_window.display();
}

void Game::handleEvents() {
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