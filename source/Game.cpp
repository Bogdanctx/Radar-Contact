//
// Created by bgd on 09.04.2024.
//

#include "../header/Game.h"

Game::Game(ResourcesManager *resourcesManager) :
            Window{resourcesManager->getResolution(), "Radar Contact"},
            m_resourcesManager{resourcesManager}
{
    addNewEntities();
    initAirports();

    aprt.setTexture(resourcesManager->getTexture("UK"));
    const std::pair<int, int> resolution = resourcesManager->getResolution();

    aprt.setScale(
            resolution.first / aprt.getLocalBounds().width,
            resolution.second / aprt.getLocalBounds().height
            );
}

void Game::update()
{
    for(Airplane &airplane: m_airplanes)
    {
        airplane.update();
    }

    if(m_newEntities_interval.getElapsedTime().asSeconds() >= 60)
    {
        addNewEntities();
        m_newEntities_interval.restart();
    }
}

void Game::render()
{
    m_window.clear();

    m_window.draw(aprt);

    for(Airplane &airplane: m_airplanes)
    {
        airplane.render(&m_window);
    }
    for(Airport &airport: m_airports)
    {
        airport.render(&m_window);
    }

    m_window.display();
}

void Game::handleEvent()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
    sf::Vector2f float_mouse_position{(float) mouse_position.x, (float) mouse_position.y};
    sf::Event game_event{};

    while(m_window.pollEvent(game_event))
    {
        for(Airplane &airplane: m_airplanes)
        {
            airplane.handleEvent(game_event, float_mouse_position);
        }

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

void Game::addNewEntities()
{
    nlohmann::json arrivals = m_dataApi.getArrivals("EGLL");
    int number_of_arrivals = arrivals.size();

    for(int i = 0; i < number_of_arrivals; i++)
    {
        std::string callsign = arrivals[i]["callsign"];
        int altitude = arrivals[i]["altitude"];
        int groundspeed = arrivals[i]["groundspeed"];
        int heading = arrivals[i]["heading"];
        std::string squawk = arrivals[i]["transponder"];

        Airplane airplane{altitude, groundspeed, heading, squawk, callsign, {500, 500}, m_resourcesManager};
        m_airplanes.push_back(airplane);
    }

}

void Game::initAirports() {
    std::unordered_map<std::string, std::pair<int, int>> airports = m_resourcesManager->getRegionAirports("UK");

    for(const auto &airport: airports) {
        const std::string icao = airport.first;
        const int x = airport.second.first;
        const int y = airport.second.second;

        const Airport newAirport{sf::Vector2f(x, y), icao};
        m_airports.push_back(newAirport);
    }

}