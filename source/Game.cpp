//
// Created by bgd on 09.04.2024.
//

#include "../header/Game.h"
#include "../header/Math.h"

Game::Game() :
            Window{{1280, 720}, "Radar Contact"},
            m_selectedRegion{"UK"},
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
    auto it = std::remove_if(m_airplanes.begin(), m_airplanes.end(), [](const Airplane &airplane) {
        return airplane.getCrashed();
    });
    m_airplanes.erase(it, m_airplanes.end());

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

void Game::checkForEntitiesCollisions() {
    std::vector<FlyingEntity*> flyingEntities;
    for(Airplane &airplane: m_airplanes) {
        auto *flyingEntity = dynamic_cast<FlyingEntity*>(&airplane);
        flyingEntities.push_back(flyingEntity);
    }

    for(FlyingEntity *A_flyingEntity: flyingEntities) {
        const std::string A_callsign = A_flyingEntity->getCallsign();
        const sf::Vector2f A_position = A_flyingEntity->getEntityPosition();
        const int A_altitude = A_flyingEntity->getAltitude();

        int conflictType = 0;

        for(FlyingEntity *B_flyingEntity: flyingEntities) {
            const std::string B_callsign = B_flyingEntity->getCallsign();
            const sf::Vector2f B_position = B_flyingEntity->getEntityPosition();
            const int B_altitude = B_flyingEntity->getAltitude();

            if(A_callsign != B_callsign) {
                int distance = Math::DistanceBetweenTwoPoints(A_position, B_position);

                if(A_altitude == B_altitude)
                {
                    if(distance <= 70) {
                        conflictType = 1;
                    }
                    if(distance <= 40) {
                        conflictType = 2;
                    }
                    if(distance <= 5) {
                        A_flyingEntity->setCrashed();
                        B_flyingEntity->setCrashed();
                    }
                }
            }
        }

        A_flyingEntity->setDanger(conflictType);
    }

}

void Game::checkInsideAirspace() {
    std::vector<FlyingEntity*> flyingEntities;
    for(Airplane &airplane: m_airplanes) {
        auto *flyingEntity = dynamic_cast<FlyingEntity*>(&airplane);
        flyingEntities.push_back(flyingEntity);
    }

    for(Airport &airport: m_airports)
    {
        for(FlyingEntity *flyingEntity: flyingEntities)
        {
            if(airport.isFlyingEntityInside(flyingEntity))
            {
                flyingEntity->setCrashed();
            }
        }
    }
}

void Game::handleEvent()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
    sf::Vector2f float_mouse_position{(float) mouse_position.x, (float) mouse_position.y};
    sf::Event game_event{};

    checkForEntitiesCollisions();
    checkInsideAirspace();

    while(m_window.pollEvent(game_event))
    {
        for(Airplane &airplane: m_airplanes) {
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
    DataAPI dataApi{};

    const nlohmann::json arrivals = dataApi.getArrivals(m_selectedRegion);
    const int number_of_arrivals = (int) arrivals.size();

    sf::Event tempEvent{};
    m_window.pollEvent(tempEvent);

    for(int i = 0; i < number_of_arrivals; i++)
    {
        const int groundspeed = arrivals[i]["groundspeed"];
        const int airspeed = groundspeed;
        const int heading = arrivals[i]["heading"];
        const int altitude = arrivals[i]["altitude"];
        const std::string squawk = arrivals[i]["transponder"];
        const std::string callsign = arrivals[i]["callsign"];
        const sf::Vector2f position{arrivals[i]["longitude"], arrivals[i]["latitude"]};
        const std::string arrival = arrivals[i]["flight_plan"]["arrival"];

        if(altitude >= 7000) {
            Airplane airplane{altitude, airspeed, heading, squawk, callsign, position, arrival};

            m_airplanes.push_back(airplane);
        }
        else if(altitude >= 2000) {

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