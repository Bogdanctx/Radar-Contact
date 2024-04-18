//
// Created by bgd on 09.04.2024.
//

#include "../header/Game.h"
#include "../header/Math.h"

Game::Game() :
            Window{{1280, 720}, "Radar Contact"},
            m_selectedRegion{"UK"},
            m_isFirstTime{true},
            weather{m_selectedRegion}
{
    std::vector<std::string> facts = ResourcesManager::Instance().getFacts();

    sf::Text randomFact{"Fact: " + facts[rand() % facts.size()], ResourcesManager::Instance().getFont("Poppins-Regular.ttf")};

    sf::FloatRect factBounds = randomFact.getLocalBounds();
    randomFact.setOrigin(factBounds.width / 2, factBounds.height / 2);
    randomFact.setPosition(640, 680);

    sf::Sprite loadingScreen{ResourcesManager::Instance().getTexture("loading_screen.png")};

    m_backgroundRegion.setTexture(ResourcesManager::Instance().getTexture(m_selectedRegion));

    m_window.draw(loadingScreen);
    m_window.draw(randomFact);
    m_window.display();

    weather.fetchWeatherImages(&m_window);
    addNewEntities();
    initAirports();

}

void Game::run()
{
    while(m_window.isOpen())
    {
        handleEvent();
        update();
        render();
    }
}

void Game::update()
{
    if(m_updateWeatherClock.getElapsedTime().asSeconds() >= 5*60) {
        weather.fetchWeatherImages(&m_window);
        m_updateWeatherClock.restart();
    }
    if(m_newEntitiesInterval.getElapsedTime().asSeconds() >= 60)
    {
        addNewEntities();
        m_newEntitiesInterval.restart();
    }

    m_window.draw(m_backgroundRegion);

    for(Airplane &airplane: m_airplanes)
    {
        airplane.update();
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
    const std::unordered_map<std::string, std::pair<int, int>> regionAirports = ResourcesManager::Instance().getRegionAirports(m_selectedRegion);
    const std::vector<float> longLatBox{ResourcesManager::Instance().getRegionBox(m_selectedRegion)};

    for(const auto &airport: regionAirports)
    {
        const std::string airportIcao = airport.first;
        const nlohmann::json arrivals = DataAPI::getArrivals(airportIcao);
        const int number_of_arrivals = (int) arrivals.size();

        sf::Event tempEvent{};
        m_window.pollEvent(tempEvent);

        for(int i = 0; i < number_of_arrivals; i++)
        {
            const std::string callsign = arrivals[i]["callsign"];
            const int altitude = arrivals[i]["altitude"];

            if(altitude >= 10000 && m_addedEntities.find(callsign) == m_addedEntities.end())
            {
                const int groundspeed = arrivals[i]["groundspeed"];
                const int airspeed = groundspeed - 130;
                const int heading = arrivals[i]["heading"];
                const std::string squawk = arrivals[i]["transponder"];
                const float latitude = arrivals[i]["latitude"];
                const float longitude = arrivals[i]["longitude"];

                const sf::Vector2f mercatorProjection = Math::MercatorProjection(latitude, longitude,
                                                                           longLatBox);

                Airplane airplane{altitude, airspeed, heading, squawk, callsign, mercatorProjection};

                m_airplanes.push_back(airplane);
                m_addedEntities.insert(callsign);
            }
        }
    }

}

void Game::initAirports() {
    std::unordered_map<std::string, std::pair<int, int>> airports = ResourcesManager::Instance().getRegionAirports("UK");

    for(const auto &airport: airports) {
        const std::string icao = airport.first;
        const int x = airport.second.first;
        const int y = airport.second.second;

        const Airport newAirport{sf::Vector2f((float)x, (float)y), icao};
        m_airports.push_back(newAirport);
    }

}