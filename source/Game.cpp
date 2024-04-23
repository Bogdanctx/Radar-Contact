//
// Created by bgd on 09.04.2024.
//

#include "../header/Game.h"
#include "../header/Math.h"

Game::Game() :
            Window{{1280, 720}, "Radar Contact"},
            m_selectedRegion{ResourcesManager::Instance().getSelectedRegion()}
{
    std::vector<std::string> facts = ResourcesManager::Instance().getFacts();

    sf::Text randomFact{"Fact: " + facts[rand() % facts.size()], ResourcesManager::Instance().getFont("Poppins-Regular.ttf")};

    sf::FloatRect factBounds = randomFact.getLocalBounds();
    randomFact.setOrigin(factBounds.width / 2, factBounds.height / 2);
    randomFact.setPosition(640, 680);

    sf::Sprite loadingScreen{ResourcesManager::Instance().getTexture("loading_screen.png")};

    m_backgroundRegion.setTexture(ResourcesManager::Instance().getTexture(m_selectedRegion));

    sf::Sound loadingSound;
    loadingSound.setBuffer(ResourcesManager::Instance().getSound("plane_landing.wav"));
    loadingSound.setPlayingOffset(sf::seconds(4));
    loadingSound.play();

    m_window.draw(loadingScreen);
    m_window.draw(randomFact);
    m_window.display();

    weather.fetchWeatherImages(&m_window);
    addNewEntities();
    initAirports();

}

void Game::run()
{
    sf::Sound loadingSound;
    loadingSound.setBuffer(ResourcesManager::Instance().getSound("atc.wav"));
    loadingSound.setLoop(true);
    loadingSound.play();


    while(m_window.isOpen())
    {
        handleEvent();
        update();
        render();
    }
}

void Game::update()
{
    removeCrashedEntities();

    if(m_updateWeatherClock.getElapsedTime().asSeconds() >= 5*60) {
        weather.fetchWeatherImages(&m_window);
        m_updateWeatherClock.restart();
    }
    if(m_newEntitiesInterval.getElapsedTime().asSeconds() >= 60)
    {
        if(rand() % 100 >= 40) {
            addNewBalloons();
        }

        addNewEntities();
        m_newEntitiesInterval.restart();
    }

    m_window.draw(m_backgroundRegion);

    for(Airplane &airplane: m_airplanes) {
        airplane.update();
    }

    for(Helicopter &helicopter: m_helicopters) {
        helicopter.update();
    }

    for(HotAirBalloon &hotAirBalloon: m_balloons) {
        hotAirBalloon.update();
    }
}

void Game::removeCrashedEntities() {

    // Stergere avion de pe harta
    auto it1 = std::remove_if(m_airplanes.begin(), m_airplanes.end(), [](const Airplane &airplane) {
        return airplane.getCrashed();
    });
    m_airplanes.erase(it1, m_airplanes.end());
    //////

    // Stergere elicopter de pe harta
    auto it2 = std::remove_if(m_helicopters.begin(), m_helicopters.end(), [](const Helicopter &helicopter) {
        return helicopter.getCrashed();
    });
    m_helicopters.erase(it2, m_helicopters.end());
    ///////

    // Stergere balon cu aer de pe harta
    auto it3 = std::remove_if(m_balloons.begin(), m_balloons.end(), [](const HotAirBalloon &balloon) {
        return balloon.getCrashed();
    });
    m_balloons.erase(it3, m_balloons.end());
    ///////
}

void Game::render()
{
    m_window.clear();

    m_window.draw(m_backgroundRegion);

    weather.render(&m_window);

    for(Airport &airport: m_airports)
    {
        airport.render(&m_window);
    }

    for(Airplane &airplane: m_airplanes)
    {
        airplane.render(&m_window);
    }

    for(Helicopter &helicopter: m_helicopters)
    {
        helicopter.render(&m_window);
    }

    for(HotAirBalloon &hotAirBalloon: m_balloons) {
        hotAirBalloon.render(&m_window);
    }

    m_window.display();
}

void Game::checkForEntitiesCollisions(const std::vector<FlyingEntity*>& flyingEntities) {
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
                    if(distance <= 35) {
                        conflictType = 1;
                    }
                    if(distance <= 15) {
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

void Game::checkInsideAirspace(const std::vector<FlyingEntity*>& flyingEntities) {
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

    std::vector<FlyingEntity*> flyingEntities;
    for(Airplane &airplane: m_airplanes) {
        auto *flyingEntity = dynamic_cast<FlyingEntity*>(&airplane);
        flyingEntities.push_back(flyingEntity);
    }
    for(Helicopter &helicopter: m_helicopters) {
        auto *flyingEntity = dynamic_cast<FlyingEntity*>(&helicopter);
        flyingEntities.push_back(flyingEntity);
    }
    for(HotAirBalloon &hotAirBalloon: m_balloons) {
        auto *flyingEntity = dynamic_cast<FlyingEntity*>(&hotAirBalloon);
        flyingEntities.push_back(flyingEntity);
    }

    checkForEntitiesCollisions(flyingEntities);
    checkInsideAirspace(flyingEntities);

    while(m_window.pollEvent(game_event))
    {
        for(Airplane &airplane: m_airplanes) {
            airplane.handleEvent(game_event, float_mouse_position);
        }
        for(Helicopter &helicopter: m_helicopters) {
            helicopter.handleEvent(game_event, float_mouse_position);
        }
        for(HotAirBalloon &hotAirBalloon: m_balloons) {
            hotAirBalloon.handleEvent(game_event, float_mouse_position);
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

void Game::addNewBalloons() {
    const int altitude{(rand() % 1301 + 200) / 100 * 100};
    const int airspeed{rand() % (130-50) + 50};
    const int heading{rand() % 360};
    const std::string squawk{"7000"};
    const std::string callsign{"BALLOON" + std::to_string(m_balloons.size() + 1)};

    std::unordered_map<std::string, std::pair<int, int>> regionAirports = ResourcesManager::Instance().getRegionAirports();

    int randomDepartureAirport = rand() % regionAirports.size();
    int randomDestination = rand() % regionAirports.size();

    if(randomDestination == randomDepartureAirport) {
        randomDestination = (randomDepartureAirport + 1) % regionAirports.size();
    }

    auto it = regionAirports.begin();
    while(randomDepartureAirport > 0) {
        randomDepartureAirport--;
        it++;
    }
    const sf::Vector2f position{(float)it->second.first, (float)it->second.second};

    std::string arrival;
    it = regionAirports.begin();
    while(randomDestination > 0) {
        randomDestination--;
        it++;
    }
    arrival = it->first;

    HotAirBalloon balloon{altitude, airspeed, heading, squawk, callsign, position, arrival};
    m_balloons.push_back(balloon);
}

void Game::addNewEntities()
{
    const nlohmann::json arrivals = dataAPI.getArrivals();
    const int number_of_arrivals = (int) arrivals.size();

    sf::Event tempEvent{};
    m_window.pollEvent(tempEvent);

    for(int i = 0; i < number_of_arrivals; i++)
    {
        const int heading = arrivals[i]["heading"];
        const int altitude = arrivals[i]["altitude"];
        const int airspeed = Math::AirspeedAtAltitude(altitude);
        const std::string squawk = arrivals[i]["transponder"];
        const std::string callsign = arrivals[i]["callsign"];
        const sf::Vector2f position{arrivals[i]["longitude"], arrivals[i]["latitude"]};
        const std::string arrival = arrivals[i]["flight_plan"]["arrival"];

        if(altitude >= 11000) {
            Airplane airplane{altitude, airspeed, heading, squawk, callsign, position, arrival};

            m_airplanes.push_back(airplane);
        }
        else if(altitude >= 2000) {
            Helicopter helicopter{altitude, airspeed, heading, squawk, callsign, position, arrival};

            m_helicopters.push_back(helicopter);
        }
    }
}

void Game::initAirports() {
    std::unordered_map<std::string, std::pair<int, int>> airports = ResourcesManager::Instance().getRegionAirports();

    for(const auto &airport: airports) {
        const std::string icao = airport.first;
        const int x = airport.second.first;
        const int y = airport.second.second;

        const Airport newAirport{sf::Vector2f((float)x, (float)y), icao};
        m_airports.push_back(newAirport);
    }

}