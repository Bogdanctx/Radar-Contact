//
// Created by bgd on 09.04.2024.
//

#include "../header/Game.h"
#include "../header/Menu.h"
#include "../header/StateMachine.h"

#include "../header/DataFetcher.h"
#include "../header/MockAPI.h"

Game::Game() :
            Window{{1280, 720}, "Radar Contact"},
            m_renderFlightsTable{false},
            m_renderWaypoints{true}
{
    loadElements();
    loadWaypoints();

    flightsTable.update(m_flyingEntities); // on first run
}

[[maybe_unused]] Game::Game(const Game& other) : Window{{1280, 720}, "Radar Contact"},
                                                m_renderFlightsTable{false},
                                                m_renderWaypoints{true}
{
    for(const auto & flyingEntity: other.m_flyingEntities) {
        m_flyingEntities.emplace_back(flyingEntity->clone());
    }
}

Game &Game::operator=(Game other) {
    swap(*this, other);
    return *this;
}

void Game::loadElements()
{
    std::vector<std::string> facts = ResourcesManager::Instance().getFacts();

    sf::Text randomFact{"Fact: " + facts[Utilities::randGen<int>(0, static_cast<int>(facts.size()) - 1)],
                        ResourcesManager::Instance().getFont("Poppins-Regular.ttf")};

    sf::FloatRect factBounds = randomFact.getLocalBounds();
    randomFact.setOrigin(factBounds.width / 2, factBounds.height / 2);
    randomFact.setPosition(640, 680);

    sf::Sprite loadingScreen{ResourcesManager::Instance().getTexture("loading_screen.png")};

    const std::string selectedRegion = ResourcesManager::Instance().getSelectedRegion();
    m_backgroundRegion.setTexture(ResourcesManager::Instance().getTexture(selectedRegion));

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

    while(m_loadingScreenDelay.getElapsedTime().asSeconds() <= 3) {
        m_window.clear();

        m_window.draw(loadingScreen);
        m_window.draw(randomFact);

        m_window.display();
    }
}

void swap(Game& game1, Game& game2) {
    using std::swap;

    swap(game1.m_flyingEntities, game2.m_flyingEntities);
}

void Game::update()
{
    checkForEntitiesCollisions();
    checkInsideWeather();
    checkInsideAirspace();
    checkOutsideScreen();

    removeCrashedEntities();

    if(m_flyingEntities.empty()) {
        m_atcSound.stop();
    }
    else {
        if(m_atcSound.getStatus() == sf::SoundSource::Stopped) {
            m_atcSound.play();
        }
    }

    if(m_flightTableClock.getElapsedTime().asSeconds() >= 5) {
        flightsTable.update(m_flyingEntities);

        m_flightTableClock.restart();
    }

    if(m_updateWeatherClock.getElapsedTime().asSeconds() >= 5*60) {
        weather.fetchWeatherImages(&m_window);
        m_updateWeatherClock.restart();
    }

    if(m_newEntitiesInterval.getElapsedTime().asSeconds() >= 4*60)
    {
        if(Utilities::randGen<int>(0, 100) >= 50) {
            addNewBalloons();
        }

        addNewEntities();
        m_newEntitiesInterval.restart();
    }

    m_window.draw(m_backgroundRegion);

    for(auto& flyingEntity: m_flyingEntities) {
        flyingEntity->update();
    }
}

void Game::checkOutsideScreen() {
    for(auto& flyingEntity: m_flyingEntities) {
        if(!flyingEntity->isInsideScreen()) {
            flyingEntity->setCrashed();
            m_fetchedFlyingEntities.erase(flyingEntity->getCallsign());
        }
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

    if (m_renderFlightsTable) {
        flightsTable.draw(&m_window);
    }

    if(m_renderWaypoints) {
        for(const auto& waypoint: m_waypoints) {
            waypoint.render(&m_window);
        }
    }

    m_window.display();
}

void Game::checkForEntitiesCollisions() {
    for(auto &A_flyingEntity: m_flyingEntities) {
        const sf::Vector2f& A_position = A_flyingEntity->getEntityPosition();
        const int A_altitude = A_flyingEntity->getAltitude();

        int conflictType = 0;

        for(auto &B_flyingEntity: m_flyingEntities) {
            if (A_flyingEntity == B_flyingEntity || A_altitude != B_flyingEntity->getAltitude()) {
                continue;
            }

            const sf::Vector2f& B_position = B_flyingEntity->getEntityPosition();
            int distance = Math::DistanceBetweenTwoPoints(A_position, B_position);

            if(distance <= 5) {
                A_flyingEntity->setCrashed();
                B_flyingEntity->setCrashed();
            }
            else if (distance <= 15) {
                conflictType = 2;
            }
            else if (distance <= 35) {
                conflictType = 1;
            }
        }

        A_flyingEntity->setDanger(conflictType);
    }
}


void Game::checkInsideWeather() {
    std::vector<sf::Sprite> weatherSprites = weather.getSprites();

    for (auto& flyingEntity : m_flyingEntities) {
        std::pair<sf::Clock, int> updateTimer = flyingEntity->getUpdateClock();

        if(updateTimer.first.getElapsedTime().asMilliseconds() < updateTimer.second) {
            continue;
        }

        const sf::Vector2i entityPosition(static_cast<int>(flyingEntity->getEntityPosition().x),
                                          static_cast<int>(flyingEntity->getEntityPosition().y));

        for (sf::Sprite& sprite: weatherSprites) {
            const sf::FloatRect& spriteBounds = sprite.getGlobalBounds();

            if (spriteBounds.contains(static_cast<sf::Vector2f>(entityPosition))) {
                int weatherDanger = Weather::getPixelColor(sprite, entityPosition);

                flyingEntity->setFallInWeather(weatherDanger);
                break;
            }
        }
    }
}

void Game::checkInsideAirspace() {
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

    while(m_window.pollEvent(gameEvent))
    {
        for(auto &flyingEntity: m_flyingEntities) {
            flyingEntity->handleEvent(gameEvent, floatMousePosition);
        }

        if(m_renderFlightsTable) {
            flightsTable.handleEvent(gameEvent, floatMousePosition);
        }

        switch(gameEvent.type)
        {
            case sf::Event::KeyPressed: {
                const sf::Keyboard::Key key_code = gameEvent.key.code;

                if (key_code == sf::Keyboard::Escape) {
                    m_window.close();
                }
                else if (key_code == sf::Keyboard::Enter) {
                    std::shared_ptr<Window> menu = std::make_shared<Menu>();
                    StateMachine::Instance().pushState(menu);
                    m_window.close();
                }
                else if (key_code == sf::Keyboard::R) {
                    m_renderFlightsTable = !m_renderFlightsTable;
                }
                else if (key_code == sf::Keyboard::T) {
                    m_renderWaypoints = !m_renderWaypoints;
                }
                else if (key_code == sf::Keyboard::Space) {
                    if (m_renderWaypoints) {
                        for (const Waypoint &wp: m_waypoints) {
                            if (wp.getBounds().contains(floatMousePosition)) {
                                for (const auto &flyingEntity: m_flyingEntities) {
                                    if (flyingEntity->getIsEntitySelected()) {
                                        if (flyingEntity->getRouteCurrentWaypoint().getName() != wp.getName()) {
                                            flyingEntity->addWaypointToRoute(wp);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else if(key_code == sf::Keyboard::C) {
                    std::vector<sf::Sprite> s = weather.getSprites();

                    for(sf::Sprite& sprite: s) {
                        if(sprite.getGlobalBounds().contains(floatMousePosition)) {
                            Weather::getPixelColor(sprite, mousePosition);
                        }
                    }
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
    const int altitude{(Utilities::randGen<int>(300, 2700)) / 100 * 100};
    const int airspeed{Utilities::randGen<int>(50, 130)};
    const int heading{Utilities::randGen<int>(0, 360)};
    const std::string squawk{"7000"};
    const std::string callsign{"BALLOON" + std::to_string(Utilities::randGen<int>(1, 1000))};

    std::unordered_map<std::string, std::pair<int, int>> regionAirports = ResourcesManager::Instance().getRegionAirports();

    const int numberOfAirports = (int) regionAirports.size();

    int randomDepartureAirport = Utilities::randGen<int>(0, numberOfAirports - 1);
    int randomDestination = Utilities::randGen<int>(0, numberOfAirports - 1);

    if(randomDestination == randomDepartureAirport) {
        randomDestination = (randomDepartureAirport + 1) % numberOfAirports;
    }

    auto it = regionAirports.begin();
    while(randomDepartureAirport > 0) {
        randomDepartureAirport--;
        it++;
    }
    const sf::Vector2f position{static_cast<float>(it->second.first), static_cast<float>(it->second.second)};

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
    const std::vector<std::string> helicopterTypes = {
            "DH8D"
    };

    const nlohmann::json arrivals = DataFetcher::getFlyingEntities(&m_window);

    const int number_of_arrivals = static_cast<int>(arrivals.size());

    sf::Event tempEvent{};
    m_window.pollEvent(tempEvent);

    for(int i = 0; i < number_of_arrivals; i++) {
        if(m_fetchedFlyingEntities.size() > 20) {
            break;
        }

        const std::string callsign = arrivals[i]["callsign"];

        if(m_fetchedFlyingEntities.contains(callsign)) {
            continue;
        }

        m_fetchedFlyingEntities.insert(callsign);

        const int heading = arrivals[i]["heading"];
        const int altitude = arrivals[i]["altitude"];
        const int airspeed = Math::AirspeedAtAltitude(altitude);
        const std::string squawk = arrivals[i]["squawk"];
        const sf::Vector2f position = Math::MercatorProjection(arrivals[i]["lat"], arrivals[i]["lon"], ResourcesManager::Instance().getRegionBox());
        const std::string arrival = arrivals[i]["arrival"];
        const std::string type = arrivals[i]["type"];

        std::shared_ptr<FlyingEntity> base;

        for(const std::string& helicopterType: helicopterTypes) {
            if(helicopterType == type) {
                Helicopter helicopter{altitude, airspeed, heading, squawk, callsign, position, arrival};

                base = std::make_shared<Helicopter>(helicopter);
            }
            else {
                Airplane airplane{altitude, airspeed, heading, squawk, callsign, position, arrival};

                base = std::make_shared<Airplane>(airplane);
            }
        }

        m_flyingEntities.push_back(base);
    }
}

void Game::initAirports() {
    std::unordered_map<std::string, std::pair<int, int>> airports = ResourcesManager::Instance().getRegionAirports();

    for(const auto &airport: airports) {
        const std::string icao = airport.first;
        const int x = airport.second.first;
        const int y = airport.second.second;

        const Airport newAirport{sf::Vector2f(x, y), icao};
        m_airports.push_back(newAirport);
    }

}

void Game::loadWaypoints() {
    const std::string waypoints = "resources/regions/" + ResourcesManager::Instance().getSelectedRegion() + "/waypoints.txt";

    std::ifstream fin(waypoints);

    int numberOfWaypoints;
    fin >> numberOfWaypoints;

    for(int i = 0; i < numberOfWaypoints; i++) {
        std::string pointName;
        int x, y;

        fin >> x >> y >> pointName;

        sf::Vector2f position(x, y);
        Waypoint waypoint{position, pointName};

        m_waypoints.push_back(waypoint);
    }

    fin.close();
}
