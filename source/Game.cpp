#include "../header/Game.h"
#include "../header/Menu.h"
#include "../header/StateMachine.h"

#include "../header/DataFetcher.h"
#include "../header/MockAPI.h"

Game::Game() :
            Window{{1280, 720}, "Radar Contact"},
            m_totalFetchedEntities{0},
            m_renderFlightsTable{false},
            m_renderWaypoints{true}
{
    DataFetcher::reset();
    loadElements();
    loadWaypoints();

    flightsTable.update(m_flyingEntities); // update flightsTable on the first run of game
}

//-----------------------------------------------------------
// Purpose: Used to load loading screen elements, sounds and
// prepare the map for play
//-----------------------------------------------------------
void Game::loadElements() {
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
    loadingSound.setVolume(30);
    loadingSound.play();

    m_atcSound.setBuffer(ResourcesManager::Instance().getSound("atc.wav"));
    m_atcSound.setLoop(true);
    m_atcSound.setVolume(50);

    // an initial draw of loading screen
    m_window.draw(loadingScreen);
    m_window.draw(randomFact);
    m_window.display();
    ////////////////////////////////////

    weather.fetchWeatherImages(&m_window);

    addNewEntities();
    initAirports();

    // if offline mode is enabled I would like the loading screen to be active for 2 seconds
    // because offline mode loads things much faster
    while(m_loadingScreenDelay.getElapsedTime().asSeconds() <= 2) {
        m_window.clear();

        m_window.draw(loadingScreen);
        m_window.draw(randomFact);

        m_window.display();
    }
}

void Game::update() {
    checkForEntitiesCollisions();
    checkInsideWeather();
    checkInsideAirspace();

    // removed out of screen flying entities
    for(auto& flyingEntity: m_flyingEntities) {
        if(!flyingEntity->isInsideScreen()) {
            flyingEntity->setCrashed();
        }
    }

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

    if(m_updateWeatherClock.getElapsedTime().asSeconds() >= 5*60) { // fetch new weather every 5 minutes
        weather.fetchWeatherImages(&m_window);
        m_updateWeatherClock.restart();
    }

    if(m_newEntitiesInterval.getElapsedTime().asSeconds() >= 6*60) { // fetch new airplanes every 6 minutes
        addNewEntities();
        m_newEntitiesInterval.restart();
    }

    m_window.draw(m_backgroundRegion);

    for(auto& flyingEntity: m_flyingEntities) {
        flyingEntity->updateCursorPosition(sf::Vector2f(sf::Mouse::getPosition(m_window)));
        flyingEntity->update();
    }
}

void Game::removeCrashedEntities() {
    auto it = std::remove_if(m_flyingEntities.begin(), m_flyingEntities.end(),
                                    [&](auto &flyingEntity) {
                                                return flyingEntity->getCrashed();
                                    });

    m_flyingEntities.erase(it, m_flyingEntities.end());
}



void Game::render() {
    m_window.clear();

    m_window.draw(m_backgroundRegion);

    weather.render(&m_window);

    for(Airport &airport: m_airports) {
        airport.render(&m_window);
    }

    if(m_renderWaypoints) {
        for(const auto& waypoint: m_waypoints) {
            waypoint.render(&m_window);
        }
    }

    for(const auto &flyingEntity: m_flyingEntities) {
        flyingEntity->render(&m_window);
    }

    if (m_renderFlightsTable) {
        flightsTable.draw(&m_window);
    }

    m_window.display();
}


//-----------------------------------------------------------
// Purpose: Used to check collisions between flying entities
// and to toggle specific flags
//-----------------------------------------------------------
void Game::checkForEntitiesCollisions() {
    for(auto& flyingEntity: m_flyingEntities) {
        FlyingEntity::Flags flag = FlyingEntity::Flags::CLEAR;
        const std::string callsign = flyingEntity->getCallsign();
        const int altitude = flyingEntity->getAltitude();

        for(auto& otherFlyingEntity: m_flyingEntities) {
            const std::string otherCallsign = otherFlyingEntity->getCallsign();

            if(callsign == otherCallsign) {
                continue;
            }
            const int otherAltitude = otherFlyingEntity->getAltitude();
            if(altitude != otherAltitude) {
                continue;
            }

            int distance = Math::DistanceBetweenTwoPoints(flyingEntity->getEntityPosition(), otherFlyingEntity->getEntityPosition());

            if(distance <= 5) {
                flyingEntity->setCrashed();
            }
            else if (distance <= 15) {
                flag = std::max(FlyingEntity::Flags::DANGER_COLLISION, flag);
            }
            else if (distance <= 35) {
                flag = std::max(FlyingEntity::Flags::WARNING_COLLISION, flag);
            }
        }

        if(flag == FlyingEntity::Flags::CLEAR && (flyingEntity->isFlagActive(FlyingEntity::Flags::DANGER_COLLISION) ||
                                                    flyingEntity->isFlagActive(FlyingEntity::Flags::WARNING_COLLISION))) {
            flyingEntity->resetFlag(FlyingEntity::Flags::DANGER_COLLISION);
            flyingEntity->resetFlag(FlyingEntity::Flags::WARNING_COLLISION);
        }
        else {
            flyingEntity->setFlag(flag);
        }
    }
}

//-----------------------------------------------------------
// Purpose: Used to check if a flying entity is inside a storm
// and toggle specific flags
//-----------------------------------------------------------
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

//-----------------------------------------------------------
// Purpose: Used to check if a flying entity is inside its
// airport destination coverage area
//-----------------------------------------------------------
void Game::checkInsideAirspace() {
    // flying entity altitude must be <= 10000 ft and speed <= 250kts
    for(Airport &airport: m_airports) {
        for(auto &flyingEntity: m_flyingEntities) {
            if(airport.isFlyingEntityInside(flyingEntity)) {
                flyingEntity->setCrashed();
            }
        }
    }
}

void Game::handleEvent() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
    sf::Vector2f floatMousePosition(mousePosition);
    sf::Event gameEvent{};

    while(m_window.pollEvent(gameEvent)) {
        for(auto &flyingEntity: m_flyingEntities) {
            flyingEntity->handleEvent(gameEvent, floatMousePosition);
        }

        if(m_renderFlightsTable) {
            flightsTable.handleEvent(gameEvent, floatMousePosition);
        }

        switch(gameEvent.type) {
            case sf::Event::KeyPressed: {
                const sf::Keyboard::Key keyCode = gameEvent.key.code;

                switch(keyCode) {
                    case sf::Keyboard::Escape: {
                        m_window.close();
                        break;
                    }
                    case sf::Keyboard::Enter: {
                        std::shared_ptr<Window> menu = std::make_shared<Menu>();
                        StateMachine::Instance().pushState(menu);
                        m_window.close();

                        break;
                    }
                    case sf::Keyboard::R: {
                        m_renderFlightsTable = !m_renderFlightsTable;
                        break;
                    }
                    case sf::Keyboard::T: {
                        m_renderWaypoints = !m_renderWaypoints;
                        break;
                    }
                    case sf::Keyboard::Space: { // add a waypoint to a flying entity's route
                        if (m_renderWaypoints) {
                            for (const Waypoint &wp: m_waypoints) {
                                if (wp.getBounds().contains(floatMousePosition)) {
                                    for (const auto &flyingEntity: m_flyingEntities) {
                                        if (flyingEntity->getIsEntitySelected() && flyingEntity->getRouteCurrentWaypoint().getName() != wp.getName()) {
                                            flyingEntity->addWaypointToRoute(wp);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }

                break;
            }
            case sf::Event::Closed: {
                m_window.close();

                break;
            }
            default:
                break;
        }
    }
}

//-----------------------------------------------------------
// Purpose: Used to populate the game with real air traffic
//-----------------------------------------------------------
void Game::addNewEntities() {
    // more will be added
    const std::vector<std::string> helicopterTypes = {
        "EC45",
        "S92",
        "EC75",
        "EC35"
    };

    const nlohmann::json arrivals = DataFetcher::getFlyingEntities(&m_window, m_totalFetchedEntities);

    if(m_fetchedFlyingEntities.size() >= DataFetcher::getFlyingEntitiesLength()) {
        m_fetchedFlyingEntities.clear();
    }

    const int numberOfArrivals = static_cast<int>(arrivals.size());

    sf::Event tempEvent{};
    m_window.pollEvent(tempEvent); // loop through window events to prevent crashes

    for(int i = 0; i < numberOfArrivals; i++) {
        if(m_flyingEntities.size() > 0) {
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
        std::string squawk = arrivals[i]["squawk"];
        const sf::Vector2f position = Math::MercatorProjection(arrivals[i]["lat"], arrivals[i]["lon"],
                                                               ResourcesManager::Instance().getRegionBox());
        const std::string arrival = arrivals[i]["arrival"];
        const std::string type = arrivals[i]["type"];

        if(Utilities::randGen<int>(1, 100) >= 95) {
            squawk = "7500";
        }

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
        ++m_totalFetchedEntities;
    }
}

//-----------------------------------------------------------
// Purpose: Used to add airports in game
//-----------------------------------------------------------
void Game::initAirports() {
    std::unordered_map<std::string, std::pair<int, int>> airports = ResourcesManager::Instance().getRegionAirports();

    for(const auto &airport: airports) {
        const std::string icao = airport.first;
        const int x = airport.second.first;
        const int y = airport.second.second;

        Airport newAirport{sf::Vector2f(x, y), icao};
        m_airports.push_back(newAirport);
    }

}

//-----------------------------------------------------------
// Purpose: Used to load the region waypoints
//-----------------------------------------------------------
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
