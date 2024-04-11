//
// Created by bgd on 09.04.2024.
//

#include "../header/Game.h"

Game::Game(ResourcesManager *resourcesManager) :
            Window{resourcesManager->GetResolution(), "Radar Contact"},
            m_resourcesManager{resourcesManager}
{
    std::string callsign = "ROT123";
    Airplane test{35000, 35000, 315, 315, 90, 7700, callsign, sf::Vector2f{500, 800}};

    m_airplanes.push_back(test);
}

void Game::update()
{
    for(Airplane &airplane: m_airplanes)
    {
        airplane.update();
    }
}

void Game::render()
{
    m_window.clear();

    for(Airplane &airplane: m_airplanes)
    {
        airplane.render(&m_window);
    }

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