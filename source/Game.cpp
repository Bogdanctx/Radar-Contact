//
// Created by bgd on 09.04.2024.
//

#include "../header/Game.h"
#include "../header/Math.h"

Game::Game(ResourcesManager &resourcesManager) :
            Window{{1280, 720}, "Radar Contact"},
            m_resourcesManager{resourcesManager},
            m_connectingToFrequency{"Connecting to radar frequency. Please wait a few seconds...",
                                    resourcesManager.getFont("Raleway-Regular.ttf"), 12},
            m_selectedRegion{"UK"},
            m_isFirstTime{true},
            weather{resourcesManager, m_selectedRegion}
{
    m_backgroundRegion.setTexture(resourcesManager.getTexture(m_selectedRegion));
    m_connectingToFrequency.setLetterSpacing(2);

    initAirports();
}

void Game::run()
{
    render();

    while(m_window.isOpen())
    {
        handleEvent();
        update();
        render();
    }
}

void Game::update()
{
    m_window.draw(m_backgroundRegion);

    for(Airplane &airplane: m_airplanes)
    {
        airplane.update();
    }

    if(m_newEntitiesInterval.getElapsedTime().asSeconds() >= 60 || m_isFirstTime)
    {
        addNewEntities();
        m_newEntitiesInterval.restart();
        m_isFirstTime = false;
    }
}

void Game::render()
{
    m_window.clear();

    m_window.draw(m_backgroundRegion);

    for(Airport &airport: m_airports)
    {
        airport.render(&m_window);
    }

    weather.render(&m_window);

    if(m_isFirstTime)
    {
        m_window.draw(m_connectingToFrequency);
    }

    for(Airplane &airplane: m_airplanes)
    {
        airplane.render(&m_window);
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
        for(Airplane &airplane: m_airplanes) {
            airplane.handleEvent(game_event, float_mouse_position);
        }
        for(Airport &airport: m_airports) {
            airport.handleEvent(game_event, float_mouse_position);
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

                if(key_code == sf::Keyboard::LAlt)
                {

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
    const std::unordered_map<std::string, std::pair<int, int>> regionAirports = m_resourcesManager.getRegionAirports(m_selectedRegion);
    const std::vector<float> longLatBox{m_resourcesManager.getRegionBox(m_selectedRegion)};

    for(const auto &airport: regionAirports)
    {
        const std::string airportIcao = airport.first;
        const nlohmann::json arrivals = DataAPI::getArrivals(airportIcao);
        const int number_of_arrivals = arrivals.size();

        for(int i = 0; i < number_of_arrivals; i++)
        {
            const std::string callsign = arrivals[i]["callsign"];
            const int altitude = arrivals[i]["altitude"];

            if(altitude >= 10000 && m_addedEntities.find(callsign) == m_addedEntities.end())
            {
                const int groundspeed = arrivals[i]["groundspeed"];
                const int heading = arrivals[i]["heading"];
                const std::string squawk = arrivals[i]["transponder"];
                const float latitude = arrivals[i]["latitude"];
                const float longitude = arrivals[i]["longitude"];

                const sf::Vector2f mercatorProjection = Math::MercatorProjection(latitude, longitude,
                                                                           longLatBox);

                Airplane airplane{altitude, groundspeed, heading, squawk, callsign, mercatorProjection,
                                  m_resourcesManager};

                m_airplanes.push_back(airplane);
                m_addedEntities.insert(callsign);
            }
        }
    }

}

void Game::initAirports() {
    std::unordered_map<std::string, std::pair<int, int>> airports = m_resourcesManager.getRegionAirports("UK");

    for(const auto &airport: airports) {
        const std::string icao = airport.first;
        const int x = airport.second.first;
        const int y = airport.second.second;

        const Airport newAirport{sf::Vector2f(x, y), icao, m_resourcesManager};
        m_airports.push_back(newAirport);
    }

}