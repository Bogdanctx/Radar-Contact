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

    m_atcSound.setBuffer(ResourcesManager::Instance().getSound("atc.wav"));
    m_atcSound.setLoop(true);

    m_window.draw(loadingScreen);
    m_window.draw(randomFact);
    m_window.display();

    weather.fetchWeatherImages(&m_window);
    addNewEntities();
    initAirports();

}

[[maybe_unused]] Game::Game(const Game& other) : Window{{1280, 720}, "Radar Contact"},
                                m_selectedRegion{ResourcesManager::Instance().getSelectedRegion()}
{
    for(const auto & flyingEntity: other.m_flyingEntities) {
        m_flyingEntities.emplace_back(flyingEntity->clone());
    }
}

Game &Game::operator=(Game other) {
    swap(*this, other);
    return *this;
}

void swap(Game& game1, Game& game2) {
    swap(game1.m_flyingEntities, game2.m_flyingEntities);
    swap(game1.m_airports, game2.m_airports);
    std::swap(game1.m_updateWeatherClock, game2.m_updateWeatherClock);
    std::swap(game1.m_newEntitiesInterval, game2.m_newEntitiesInterval);
    std::swap(game1.m_backgroundRegion, game2.m_backgroundRegion);
    std::swap(game1.m_atcSound, game2.m_atcSound);
    swap(game1.m_selectedRegion, game2.m_selectedRegion);
    swap(game1.weather, game2.weather);
    swap(game1.dataAPI, game2.dataAPI);
    swap(game1.ozn, game2.ozn);
}

void Game::update()
{
    removeCrashedEntities();

    if(m_flyingEntities.empty()) {
        m_atcSound.stop();
    }
    else {
        if(m_atcSound.getStatus() == sf::SoundSource::Stopped) {
            m_atcSound.play();
        }
    }

    if(m_passingOZN.getElapsedTime().asSeconds() >= 40) {
        addNewOZN();

        m_passingOZN.restart();
    }

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

    for(auto &flyingEntity: m_flyingEntities) {
        flyingEntity->update();
    }

    sf::Vector2f oznPosition = ozn.getEntityPosition();

    if(oznPosition.x >= -15 && oznPosition.x <= 1300 && oznPosition.y >= -15 && oznPosition.y <= 745) {
        ozn.update();
    }
}

void Game::removeCrashedEntities() {
    auto it1 = std::remove_if(m_flyingEntities.begin(), m_flyingEntities.end(), [](auto &flyingEntity) {
        return flyingEntity->getCrashed();
    });
    m_flyingEntities.erase(it1, m_flyingEntities.end());
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

    for(const auto &flyingEntity: m_flyingEntities) {
        flyingEntity->render(&m_window);
    }

    ozn.render(&m_window);

    m_window.display();
}

void Game::checkForEntitiesCollisions() {
    for(auto &A_flyingEntity: m_flyingEntities) {
        const std::string A_callsign = A_flyingEntity->getCallsign();
        const sf::Vector2f A_position = A_flyingEntity->getEntityPosition();
        const int A_altitude = A_flyingEntity->getAltitude();

        int conflictType = 0;

        for(auto &B_flyingEntity: m_flyingEntities) {
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

void Game::checkInsideAirspace() { // check if a flying entity could be controlled by a inferior ATC level
    // flying entity altitude must be <= 10000 ft and speed <= 250kts
    for(Airport &airport: m_airports)
    {
        for(auto &flyingEntity: m_flyingEntities)
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
    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
    sf::Vector2f floatMousePosition{(float) mousePosition.x, (float) mousePosition.y};
    sf::Event gameEvent{};

    checkForEntitiesCollisions();
    checkInsideAirspace();

    while(m_window.pollEvent(gameEvent))
    {
        for(auto &flyingEntity: m_flyingEntities) {
            flyingEntity->handleEvent(gameEvent, floatMousePosition);
        }
        ozn.handleEvent(gameEvent, floatMousePosition);

        switch(gameEvent.type)
        {
            case sf::Event::KeyPressed:
            {
                const sf::Keyboard::Key key_code = gameEvent.key.code;

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

void Game::addNewOZN() {
    enum Sides {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };
    const int spawnSide = rand() % 4;
    sf::Vector2f position;
    int heading;

    switch (spawnSide) {
        case Sides::NORTH:
        {
            position.x = (float) (rand() % (900 - 50) + 50);
            position.y = 0;
            heading = rand() % (225 - 145) + 145;
            break;
        }
        case Sides::EAST:
        {
            position.x = 1280;
            position.y = (float) (rand() % (500 - 20) + 20);
            heading = rand() % (290 - 245) + 245;
            break;
        }
        case Sides::SOUTH:
        {
            position.x = (float) (rand() % (900 - 50) + 50);
            position.y = 1280;
            heading = rand() % (385 - 330) + 330;
            break;
        }
        case Sides::WEST:
        {
            position.x = 0;
            position.y = (float) (rand() % (500 - 20) + 20);
            heading = rand() % (120 - 60) + 60;
            break;
        }
        default:
            heading = 0;
            break;
    }

    const int altitude{(rand() % (500000 - 60000) + 60000) / 100 * 100};
    const int airspeed{rand() % (2500-1000) + 1000};
    const std::string squawk{"0000"};
    const std::string callsign{"OZN"};
    const std::string arrival = "ANDROMEDA";

    ozn = OZN{altitude, airspeed, heading, squawk, callsign, position, arrival};
}

void Game::addNewBalloons() {
    const int altitude{(rand() % 1301 + 200) / 100 * 100};
    const int airspeed{rand() % (130-50) + 50};
    const int heading{rand() % 360};
    const std::string squawk{"7000"};
    const std::string callsign{"BALLOON" + std::to_string(rand() % 1000)};

    std::unordered_map<std::string, std::pair<int, int>> regionAirports = ResourcesManager::Instance().getRegionAirports();

    const int numberOfAirports = (int) regionAirports.size();

    int randomDepartureAirport = rand() % numberOfAirports;
    int randomDestination = rand() % numberOfAirports;

    if(randomDestination == randomDepartureAirport) {
        randomDestination = (randomDepartureAirport + 1) % numberOfAirports;
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

    std::shared_ptr<FlyingEntity> base = std::make_shared<HotAirBalloon>(balloon);
    m_flyingEntities.push_back(base);
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
        std::string callsign = arrivals[i]["callsign"];
        const sf::Vector2f position{arrivals[i]["longitude"], arrivals[i]["latitude"]};
        const std::string arrival = arrivals[i]["flight_plan"]["arrival"];

        if(altitude >= 11000) {
            Airplane airplane{altitude, airspeed, heading, squawk, callsign, position, arrival};

            std::shared_ptr<FlyingEntity> base = std::make_shared<Airplane>(airplane);
            m_flyingEntities.push_back(base);
        }
        else if(altitude >= 2000) {
            const std::vector<std::string> helicopterCallsigns = {
                    "Rotor",
                    "Blackhawk",
                    "UH",
                    "Medevac"
            };

            callsign = helicopterCallsigns[rand() % helicopterCallsigns.size()] + std::to_string(rand() % 100 + 1);
            Helicopter helicopter{altitude, airspeed, heading, squawk, callsign, position, arrival};

            std::shared_ptr<FlyingEntity> base = std::make_shared<Helicopter>(helicopter);
            m_flyingEntities.push_back(base);
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