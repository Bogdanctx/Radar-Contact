#include "Game.hpp"
#include "Menu.hpp"
#include "StateMachine.hpp"
#include "Helicopter.hpp"
#include "Airplane.hpp"
#include "ResourcesManager.hpp"
#include "Math.hpp"
#include "MockAPI.hpp"
#include "OneDecimalFloatingPoint.h"

Game::Game(const std::string& selectedRegion, bool usingLiveAPI) : AppWindow(1280, 720),
    m_atcSound(ResourcesManager::Instance().getSound("atc.wav")),
    m_region(selectedRegion)

{
    if(usingLiveAPI)
    {
        m_api = std::make_shared<LiveAPI>(m_region);
    }
    else {
        m_api = std::make_shared<MockAPI>(m_region);
    }

    loadElements();
    loadWaypoints();

    flightsTable.update(m_flyingEntities); // update flightsTable on the first run of game
}

//-----------------------------------------------------------
// Purpose: Used to load loading screen elements, sounds and
// prepare the map for play
//-----------------------------------------------------------
void Game::loadElements() {
    sf::Sound loadingSound(ResourcesManager::Instance().getSound("plane_landing.wav"));
    loadingSound.setPlayingOffset(sf::seconds(4));
    loadingSound.setVolume(30);
    loadingSound.play();

    m_atcSound.setLooping(true);
    m_atcSound.setVolume(50);

    std::future<void> future = std::async(std::launch::async, [this]()
    {
        m_api->downloadWeatherTextures();
        weather.updateImages(m_api->getWeatherTextures(), m_region.getBounds(), m_region.getWeatherTiles());
        addNewEntities();
        initAirports();
    });

    setLoadingScreen(future);
}

void Game::setLoadingScreen(const std::future<void>& future)
{
    std::vector<std::string> facts = ResourcesManager::Instance().getFacts();
    sf::Text randomFact(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"),
                        "Fact: " + facts[Utility::randomNumber(0, static_cast<int>(facts.size()) - 1)]);

    sf::FloatRect factBounds = randomFact.getLocalBounds();
    randomFact.setOrigin(factBounds.position + factBounds.size / 2.f);
    randomFact.setPosition(sf::Vector2f(640, 680));

    sf::Sprite loadingScreen{ResourcesManager::Instance().getTexture("loading_screen.png")};

    Utility::Timer m_loadingScreenDelay{2000};

    while(future.wait_for(std::chrono::microseconds(200)) != std::future_status::ready || !m_loadingScreenDelay.passedDelay())
    {
        while(m_window.pollEvent()) {} // poll events to prevent crashes

        m_window.clear();
        m_window.draw(loadingScreen);
        m_window.draw(randomFact);
        m_window.display();
    }
}


void Game::internalUpdate() {
    checkForEntitiesCollisions();
    checkInsideWeather();
    checkInsideAirspace();

    // removed out of screen flying entities
    for(std::shared_ptr<FlyingEntity> &flyingEntity: m_flyingEntities) {
        const sf::Vector2f position = flyingEntity->getEntityPosition();
        const bool insideScreen = 0 <= position.x && position.x <= 1280 && 0 <= position.y && position.y <= 720;

        if(!insideScreen) {
            flyingEntity->setCrashed();
        }
    }

    removeCrashedEntities();

    if(m_flyingEntities.empty()) {
        m_atcSound.stop();
    }
    else {
        if(m_atcSound.getStatus() == sf::SoundSource::Status::Stopped) {
            m_atcSound.play();
        }
    }

    if(m_flightTableClock.passedDelay()) {
        flightsTable.update(m_flyingEntities);

        m_flightTableClock.restart();
    }

    if(m_updateWeatherClock.passedDelay() && !weatherThreadLaunched) { // change weather every 5 minutes
        weatherThreadLaunched = true;

        // using thread because std::async is shortly freezing the UI
        std::thread([this]()
        {
            m_api->downloadWeatherTextures();
            weather.updateImages(m_api->getWeatherTextures(), m_region.getBounds(), m_region.getWeatherTiles());
            weatherThreadLaunched = false;
        }).detach();

        m_updateWeatherClock.restart();
    }


    if(m_newEntitiesInterval.passedDelay() && !airtrafficThreadLaunched) { // add new airplanes every 6 minutes
        airtrafficThreadLaunched = true;

        std::thread([this]()
        {
            addNewEntities();

            airtrafficThreadLaunched = false;
        }).detach();

        m_newEntitiesInterval.restart();
    }

    for(std::shared_ptr<FlyingEntity> &flyingEntity: m_flyingEntities) {
        flyingEntity->update(positionRelativeToView(sf::Mouse::getPosition(m_window)));
    }
}


void Game::removeCrashedEntities() {
    m_flyingEntities.remove_if([](const std::shared_ptr<FlyingEntity> &flyingEntity)
    {
        return flyingEntity->getCrashed();
    });
}

void Game::internalRender() {
    m_region.render(&m_window);

    weather.render(&m_window);

    for(const Airport &airport: m_airports) {
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
        flightsTable.render(&m_window);
    }
}


//-----------------------------------------------------------
// Purpose: Used to check collisions between flying entities
// and to toggle specific flags
//-----------------------------------------------------------
void Game::checkForEntitiesCollisions() {
    for(std::shared_ptr<FlyingEntity> &flyingEntity: m_flyingEntities) {
        FlyingEntity::Flags flag = FlyingEntity::Flags::CLEAR;
        const std::string callsign = flyingEntity->getCallsign();
        const int altitude = flyingEntity->getAltitude();

        for(const auto& otherFlyingEntity: m_flyingEntities) {
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

    for (std::shared_ptr<FlyingEntity> &flyingEntity : m_flyingEntities) {
        if(!flyingEntity->canUpdate()) {
            continue;
        }

        const sf::Vector2i entityPosition = static_cast<sf::Vector2i>(flyingEntity->getEntityPosition());

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
void Game::checkInsideAirspace() const
{
    // flying entity altitude must be <= 10000 ft and speed <= 250kts
    for(const std::shared_ptr<FlyingEntity> &flyingEntity: m_flyingEntities)
    {
        if(flyingEntity->getAltitude() <= 10000 && flyingEntity->getAirspeed() <= 250)
        {
            for(const Airport &airport: m_airports)
            {
                if(flyingEntity->getArrival() == airport.getIcao())
                {
                    if(airport.getBounds().contains(flyingEntity->getEntityPosition()) &&
                        flyingEntity->getFuel() <= OneDecimalFloatingPoint(10, 0))
                    {
                        flyingEntity->setCrashed();
                    }
                }
            }
        }
    }
}

void Game::internalHandleEvent(const std::optional<sf::Event>& event)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

    for(auto &flyingEntity: m_flyingEntities) {
        flyingEntity->handleEvent(event, positionRelativeToView(mousePosition));
    }

    if(m_renderFlightsTable) {
        flightsTable.handleEvent(event, positionRelativeToView(mousePosition));
    }

    if(event->is<sf::Event::KeyPressed>())
    {
        sf::Keyboard::Key keyCode = event->getIf<sf::Event::KeyPressed>()->code;
        switch(keyCode)
        {
            case sf::Keyboard::Key::Enter:
            {
                std::shared_ptr<AppWindow> menu = std::make_shared<Menu>();
                StateMachine::Instance().pushState(menu);
                m_window.close();

                break;
            }

            case sf::Keyboard::Key::R:
            {
                m_renderFlightsTable = !m_renderFlightsTable;
                break;
            }

            case sf::Keyboard::Key::T:
            {
                m_renderWaypoints = !m_renderWaypoints;
                break;
            }

            case sf::Keyboard::Key::Space:
            { // add a waypoint to a flying entity's route
                if (m_renderWaypoints)
                {
                    for (const Waypoint &wp: m_waypoints)
                    {
                        if (wp.getBounds().contains(positionRelativeToView(mousePosition)))
                        {
                            auto ret = std::ranges::find_if(m_flyingEntities.begin(), m_flyingEntities.end(),
                                [&wp](const std::shared_ptr<FlyingEntity>& flyingEntity)
                            {
                                return flyingEntity->getIsEntitySelected() &&
                                    flyingEntity->getRouteCurrentWaypoint().getName() != wp.getName();
                            });

                            if(ret != m_flyingEntities.end())
                            {
                                (*ret)->addWaypointToRoute(wp);
                            }
                        }
                    }
                }

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
void Game::addNewEntities()
{
    // more will be added
    const std::vector<std::string> helicopterTypes = {
        "EC45",
        "S92",
        "EC75",
        "EC35",
        "A189"
    };

    const nlohmann::json fetched = fetchNewFlyingEntities();
    std::vector<nlohmann::json> arrivals(fetched.begin(), fetched.end());

    const int numberOfArrivals = static_cast<int>(arrivals.size());

    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(arrivals.begin(), arrivals.end(), rng);

    for(int i = 0; i < numberOfArrivals; i++)
    {
        if(m_flyingEntities.size() > 8)
        {
            break;
        }

        const std::string callsign = arrivals[i]["callsign"];

        if(m_fetchedFlyingEntities.contains(callsign))
        {
            continue;
        }

        m_fetchedFlyingEntities.insert(callsign);

        const int heading = arrivals[i]["heading"];
        const int altitude = arrivals[i]["altitude"];
        const int airspeed = Math::AirspeedAtAltitude(altitude);
        std::string squawk = arrivals[i]["squawk"];
        const sf::Vector2f position = Math::MercatorProjection(arrivals[i]["lat"], arrivals[i]["lon"],
                                                               m_region.getBounds());
        const std::string arrival = arrivals[i]["arrival"];
        const std::string type = arrivals[i]["type"];

        // even though the squawk of other airplanes is real I want to force a hijacking scenario sometimes
        if(Utility::randomNumber(1, 100) >= 97)
        {
            squawk = "7500";
        }

        std::shared_ptr<FlyingEntity> base;
        bool helicopterAdded = false;

        for(const std::string& helicopterType: helicopterTypes)
        {
            if(helicopterType == type)
            {
                Helicopter helicopter{altitude, airspeed, heading, squawk, callsign, position, arrival};

                base = std::make_shared<Helicopter>(helicopter);
                helicopterAdded = true;
            }
        }

        if(!helicopterAdded)
        {
            Airplane airplane{altitude, airspeed, heading, squawk, callsign, position, arrival};

            base = std::make_shared<Airplane>(airplane);
        }

        m_usedDownloadedData++;
        m_flyingEntities.push_back(base);
    }
}

nlohmann::json Game::fetchNewFlyingEntities()
{
    // All data downloaded from API must be used before requesting new data from API
    // This is to prevent spamming the API
    if(m_downloadedFlyingEntities.is_null() || m_usedDownloadedData >= static_cast<int>(m_incomingFlyingEntities.size())) {
        m_downloadedFlyingEntities = m_api->downloadFlyingEntities();
        m_incomingFlyingEntities.clear();
        m_usedDownloadedData = 0;
    }
    else {
        return m_incomingFlyingEntities;
    }

    const std::vector<std::string> regionAirports = m_region.getAirportsIcao();

    for(auto& item : m_downloadedFlyingEntities) {
        if(item["flight"].is_null() || item["t"].is_null() || item["alt_baro"].is_null() || item["alt_baro"].is_string() ||
           item["lon"].is_null() || item["lat"].is_null() || item["track"].is_null() || item["t"].is_null() || item["gs"].is_null()) {
            continue;
        }

        int airspeed = item["gs"];
        if(airspeed < 120) {
            continue;
        }

        int altitude = item["alt_baro"];
        altitude = altitude / 1000 * 1000;

        if(altitude < 2000) {
            continue;
        }

        int randomIndex = Utility::randomNumber(0, static_cast<int>(regionAirports.size() - 1));
        const std::string& randomAirport = regionAirports[randomIndex];

        if(item["squawk"].is_null()) {
            item["squawk"] = std::to_string(Utility::randomNumber(1000, 9999));
        }

        // remove the last 3 white spaces from the back of the callsign
        std::string callsign = item["flight"];
        callsign.resize(callsign.size() - 2);

        nlohmann::json flyingEntity = {
                {"callsign", callsign},
                {"altitude", altitude},
                {"squawk",   item["squawk"]},
                {"lon",      static_cast<float>(item["lon"])},
                {"lat",      static_cast<float>(item["lat"])},
                {"heading",  static_cast<int>(item["track"])},
                {"arrival",  randomAirport},
                {"type",     item["t"]}
        };

        m_incomingFlyingEntities.push_back(flyingEntity);

        while(m_window.pollEvent()) {} // poll through window events to prevent crashes
    }

    return m_incomingFlyingEntities;
}


//-----------------------------------------------------------
// Purpose: Used to add airports in game
//-----------------------------------------------------------
void Game::initAirports()
{
    const std::unordered_map<std::string, std::pair<int, int>> airports = m_region.getAirports();

    for(const auto &[airportIcao, position]: airports)
    {
        const std::string icao = airportIcao;
        const int x = position.first;
        const int y = position.second;

        Airport newAirport{sf::Vector2f(x, y), icao};
        m_airports.push_back(newAirport);
    }
}

//-----------------------------------------------------------
// Purpose: Used to load the region waypoints
//-----------------------------------------------------------
void Game::loadWaypoints()
{
    const std::string waypoints = "resources/regions/" + m_region.getName() + "/waypoints.txt";

    std::ifstream fin(waypoints);

    int numberOfWaypoints;
    fin >> numberOfWaypoints;

    for(int i = 0; i < numberOfWaypoints; i++)
    {
        std::string pointName;
        int x, y;

        fin >> x >> y >> pointName;

        sf::Vector2f position(x, y);
        Waypoint waypoint{position, pointName};

        m_waypoints.push_back(waypoint);
    }

    fin.close();
}
