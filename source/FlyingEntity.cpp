#include "../header/FlyingEntity.h"
#include "../header/Math.h"
#include "../header/ResourcesManager.h"
#include "../header/Weather.h"

FlyingEntity::FlyingEntity(int altitude, int speed, int heading, const std::string &squawk, const std::string &callsign,
                           sf::Vector2f position, const std::string &arrival) :
        m_entitySelected{false},
        m_callsignText{callsign, ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_heading{heading}, m_speed{speed},
        m_altitude{altitude},
        m_fuel{Utilities::randGen<int>(12, 18), Utilities::randGen<int>(0, 9)},
        m_newHeading{heading},
        m_newAltitude{altitude},
        m_newSpeed{speed},
        m_fallInWeather{Weather::RainDanger::Clear},
        m_isCrashed{false},
        m_hijackChangesInterval{0},
        m_lostCommsInterval{0},
        m_fuelConsumptionInterval{4.5},
        hasFuel{true},
        m_arrival{arrival}, m_arrivalText{arrival, ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_squawk{squawk}, m_squawkText(squawk, ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10),
        m_routeWaypointsText{"", ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_minSpeed{140},
        m_maxSpeed{320},
        m_minAltitude{2000},
        m_maxAltitude{43000},
        m_headingText{std::to_string(heading), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_speedText{std::to_string(speed), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_altitudeText{std::to_string(altitude), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_fuelText{m_fuel.asString(), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_newHeadingText{std::to_string(m_newHeading), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_newSpeedText{std::to_string(speed), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_newAltitudeText{std::to_string(altitude), ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 10},
        m_callsign{callsign}, m_headingStick{sf::Vector2f(26, 1.2f)}
{
    m_entity.setSize(sf::Vector2f(10, 10));
    m_entity.setFillColor(sf::Color::White);
    m_entity.setOrigin(sf::Vector2f(5, 5)); // set origin in middle
    m_entity.setPosition(position);

    m_newAltitudeText.setFillColor(sf::Color::Cyan);
    m_newSpeedText.setFillColor(sf::Color::Cyan);
    m_newHeadingText.setFillColor(sf::Color::Cyan);

    m_headingStick.setFillColor(sf::Color::Cyan);
    m_headingStick.setPosition(position);
    m_headingStick.setSize(sf::Vector2f(26.f, 1.2f));
    m_headingStick.setRotation(heading - 90);

    if(squawk == "7700") {
        setFlag(Flags::GENERAL_EMERGENCY);
    }
    else if(squawk == "7600") {
        setFlag(Flags::LOST_COMMS);
    }
    else if(squawk == "7500") {
        setFlag(Flags::HIJACK);
    }

    updateText();
}

void FlyingEntity::updateText() {
    if(m_entitySelected) {
        const sf::Vector2f position = m_entity.getPosition();
        float xOffset;

        m_callsignText.setPosition(position.x - 8, position.y - 30);

        xOffset = position.x - 8 + m_callsignText.getLocalBounds().width + 5;
        m_squawkText.setPosition(xOffset, position.y - 30);
        xOffset += m_squawkText.getLocalBounds().width + 5;
        m_arrivalText.setPosition(xOffset, position.y - 30);

        xOffset += m_arrivalText.getLocalBounds().width + 5;
        m_routeWaypointsText.setPosition(xOffset, position.y - 30);

        xOffset = position.x - 8;
        m_fuelText.setPosition(xOffset, position.y - 20);

        xOffset += m_fuelText.getLocalBounds().width + 5;
        m_speedText.setPosition(xOffset, position.y - 20);

        xOffset += m_speedText.getLocalBounds().width + 5;
        m_headingText.setPosition(xOffset, position.y - 20);

        xOffset += m_headingText.getLocalBounds().width + 5;
        m_altitudeText.setPosition(xOffset, position.y - 20);

        xOffset += m_altitudeText.getLocalBounds().width + 5;
        m_newSpeedText.setPosition(xOffset, position.y - 20);

        xOffset += m_newSpeedText.getLocalBounds().width + 5;
        m_newHeadingText.setPosition(xOffset, position.y - 20);

        xOffset += m_newHeadingText.getLocalBounds().width + 5;
        m_newAltitudeText.setPosition(xOffset, position.y - 20);

        m_headingStick.setPosition(position.x, position.y);
    }
    else {
        const sf::Vector2f position = m_entity.getPosition();

        m_callsignText.setPosition(position.x - 5, position.y - 20);
    }
}

void FlyingEntity::render(sf::RenderWindow* gameWindow) {
    gameWindow->draw(m_entity);
    gameWindow->draw(m_callsignText);

    if(m_entitySelected) {
        gameWindow->draw(m_arrivalText);
        gameWindow->draw(m_headingText);
        gameWindow->draw(m_speedText);
        gameWindow->draw(m_altitudeText);
        gameWindow->draw(m_squawkText);
        gameWindow->draw(m_routeWaypointsText);
        gameWindow->draw(m_fuelText);

        gameWindow->draw(m_newSpeedText);
        gameWindow->draw(m_newAltitudeText);
        gameWindow->draw(m_newHeadingText);
        gameWindow->draw(m_headingStick);
    }
}

void FlyingEntity::updateCursorPosition(const sf::Vector2f position) {
    m_mousePosition = position;
}

void FlyingEntity::handleEvent(const sf::Event& gameEvent, const sf::Vector2f mousePosition) {
    if(m_entitySelected) {
        checkAltitudeChange(); // check if user is changing entity altitude
        checkSpeedChange(); // check if user is changing entity speed
        checkHeadingChange(); // check if user is changing entity heading
    }

    switch(gameEvent.type) {
        case sf::Event::MouseButtonPressed: {
            sf::FloatRect entityBounds = m_entity.getGlobalBounds();

            // if an entity has been selected by user
            if(entityBounds.contains(mousePosition)) {
                m_entitySelected = true;
                updateText();
            }
            else {
                m_entitySelected = false;
            }
        }

        default:
            break;
    }
}

void FlyingEntity::addWaypointToRoute(const Waypoint& waypoint) {
    route.push_back(waypoint);

    m_routeWaypoints += waypoint.getName() + ' ';
    m_routeWaypointsText.setString(m_routeWaypoints);
}

void FlyingEntity::checkAltitudeChange() {
    if(isFlagActive(Flags::LOST_COMMS) || isFlagActive(Flags::HIJACK)) {
        return;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        if(m_newAltitude + 100 <= m_maxAltitude && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            setNewAltitude(m_newAltitude + 100);
        }
        if(m_newAltitude - 100 >= m_minAltitude && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            setNewAltitude(m_newAltitude - 100);
        }
    }
}

void FlyingEntity::checkSpeedChange() {
    if(isFlagActive(Flags::LOST_COMMS) || isFlagActive(Flags::HIJACK)) {
        return;
    }

    if(sf::Keyboard::isKeyPressed((sf::Keyboard::LAlt))) {
        if(m_newSpeed + 1 <= m_maxSpeed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            setNewSpeed(m_newSpeed + 1);
        }
        if(m_newSpeed - 1 >= m_minSpeed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            setNewSpeed(m_newSpeed - 1);
        }
    }
}

void FlyingEntity::update() {
    updateAltitudeData();
    updateSpeedData();
    updateHeadingData();
    updateFuel();

    if(isFlagActive(Flags::DANGER_COLLISION) || isFlagActive(Flags::HIJACK) || isFlagActive(Flags::LOST_COMMS)) {
        m_entity.setFillColor(sf::Color::Red);
    }
    else if(isFlagActive(Flags::WARNING_COLLISION) || isFlagActive(Flags::GENERAL_EMERGENCY)) {
        m_entity.setFillColor(sf::Color(230, 140, 44));
    }
    else if(isFlagActive(Flags::LOW_FUEL)) {
        m_entity.setFillColor(sf::Color(209, 138, 138));
    }
    else {
        m_entity.setFillColor(sf::Color::White);
    }

    if(isFlagActive(Flags::HIJACK) && m_hijackChangesClock.getElapsedTime().asSeconds() >= m_hijackChangesInterval) {
        hijackUpdateData();

        m_hijackChangesInterval = Utilities::randGen<int>(14, 28);
        m_hijackChangesClock.restart();
    }
    if(m_squawk == "7600" && m_lostCommsClock.getElapsedTime().asSeconds() >= m_lostCommsInterval) {
        if(isFlagActive(Flags::LOST_COMMS)) {
            resetFlag(Flags::LOST_COMMS);
        }
        else {
            setFlag(Flags::LOST_COMMS);
        }
        m_lostCommsInterval = Utilities::randGen<int>(9, 18);
        m_lostCommsClock.restart();
    }

    if(m_clocks.m_updateClock.getElapsedTime().asMilliseconds() >= m_clocks.m_updateInterval) {
        internalUpdate();
        
        m_clocks.m_updateClock.restart();
        
        switch (m_fallInWeather) {
            case Weather::RainDanger::Blue: {
                setAltitude(m_altitude + Utilities::randGen<int>(-100, 100) / 100 * 100);
                setHeading(m_heading + Utilities::randGen<int>(-2, 2));
                setSpeed(m_speed + Utilities::randGen<int>(-2, 2));

                break;
            }
            case Weather::RainDanger::Yellow: {
                setAltitude(m_altitude + Utilities::randGen<int>(-400, 200) / 100 * 100);
                setHeading(m_heading + Utilities::randGen<int>(-10, 10));
                setSpeed(m_speed + Utilities::randGen<int>(-5, 5));

                break;
            }
            case Weather::RainDanger::Red: {
                setAltitude(m_altitude + Utilities::randGen<int>(-800, 100) / 100 * 100);
                setHeading(m_heading + Utilities::randGen<int>(-15, 15));
                setSpeed(m_speed + Utilities::randGen<int>(-10, 10));

                break;
            }
            case Weather::RainDanger::Pink: {
                setAltitude(m_altitude + Utilities::randGen<int>(-1000, 0) / 100 * 100);
                setHeading(m_heading + Utilities::randGen<int>(-25, 25));
                setSpeed(m_speed + Utilities::randGen<int>(-16, 16));

                break;
            }
            default:
                break;
        }

        if(m_altitude <= 0 || m_speed <= m_minSpeed) {
            setCrashed();
        }

        updateText();

        // if no direction is choosen, then heading stick might be updated
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            m_headingStick.setRotation(m_heading - 90);
        }

        if(!route.empty()) {
            sf::Vector2f waypointPosition = route.front().getPosition();
            int distance = Math::DistanceBetweenTwoPoints(m_entity.getPosition(), waypointPosition);

            if(distance <= 3) {
                route.pop_front();
            }
        }
        else {
            m_routeWaypoints = "";
            m_routeWaypointsText.setString(m_routeWaypoints);
        }
    }
}

void FlyingEntity::setSpeed(int speed) {
    m_speed = speed;
    m_speedText.setString(std::to_string(m_speed));
}

void FlyingEntity::setAltitude(int altitude) {
    m_altitude = altitude;
    m_altitudeText.setString(std::to_string(m_altitude));
}

void FlyingEntity::setHeading(int heading) {
    m_heading = heading;
    m_headingText.setString(std::to_string(m_heading));
}


void FlyingEntity::setNewSpeed(int newSpeed) {
    m_newSpeed = newSpeed;
    m_newSpeedText.setString(std::to_string(m_newSpeed));
}

void FlyingEntity::setNewAltitude(int newAltitude) {
    m_newAltitude = newAltitude;
    m_newAltitudeText.setString(std::to_string(m_newAltitude));
}

void FlyingEntity::setNewHeading(int newHeading) {
    m_newHeading = newHeading;
    m_newHeadingText.setString(std::to_string(m_newHeading));
    m_headingStick.setRotation(newHeading - 90);
}

void FlyingEntity::updateFuel() {
    if(!hasFuel) {
        return;
    }

    if(m_fuelConsumptionClock.getElapsedTime().asSeconds() >= m_fuelConsumptionInterval) {
        --m_fuel;
        m_fuelText.setString(m_fuel.asString());
        m_fuelConsumptionClock.restart();

        if(m_fuel <= Utilities::OneDecimalFloatingPoint(3, 0)) {
            setFlag(Flags::LOW_FUEL);
        }

        if(m_fuel == Utilities::OneDecimalFloatingPoint(0, 0)) {
            hasFuel = false;
            m_altitude -= 100;
            m_speed--;
        }
    }

    if (m_speed <= m_newSpeed) { // is reducing speed
        if (m_altitude < m_newAltitude) { // is descending
            m_fuelConsumptionInterval = 2.5; // Less fuel needed when reducing speed and descending
        } else {
            m_fuelConsumptionInterval = 3.5; // Moderate fuel needed when reducing speed and maintaining/climbing
        }
    } else { // is increasing speed
        if (m_altitude <= m_newAltitude) {
            m_fuelConsumptionInterval = 3.8; // Moderate fuel needed when increasing speed and descending/maintaining
        } else {
            m_fuelConsumptionInterval = 7.0; // More fuel needed when increasing speed and climbing
        }
    }

    if (m_speed == m_newSpeed && m_altitude == m_newAltitude) {
        m_fuelConsumptionInterval = 4.5; // Moderate fuel consumption when maintaining speed and altitude
    }

}

void FlyingEntity::checkHeadingChange() {
    if(isFlagActive(Flags::LOST_COMMS) || isFlagActive(Flags::HIJACK)) {
        return;
    }

    if(sf::Keyboard::isKeyPressed((sf::Keyboard::LShift))) {
        int dir = Math::DirectionToPoint(m_entity.getPosition(), m_mousePosition);
        setNewHeading(dir);

        while(!route.empty()) {
            route.pop_front();
        }

        m_routeWaypoints = "";
        m_routeWaypointsText.setString(m_routeWaypoints);
    }
}

std::pair<sf::Clock, int> FlyingEntity::getUpdateClock() const {
    return std::make_pair(m_clocks.m_updateClock, m_clocks.m_updateInterval);
}

void FlyingEntity::setClocks(const FlyingEntity::Clocks clocks) {
    m_clocks = clocks;
}

void FlyingEntity::setAltitudeConstraints(int minAltitude, int maxAltitude) {
    m_minAltitude = minAltitude;
    m_maxAltitude = maxAltitude;
}

void FlyingEntity::setSpeedConstraints(int minSpeed, int maxSpeed) {
    m_minSpeed = minSpeed;
    m_maxSpeed = maxSpeed;
}

void FlyingEntity::updateAltitudeData() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || m_altitude == m_newAltitude) {
        return;
    }

    if(m_clocks.m_altitudeClock.getElapsedTime().asMilliseconds() >= m_clocks.m_altitudeInterval) {
        if(!hasFuel) {
            setAltitude(m_altitude - Utilities::randGen<int>(100, 1000) / 100 * 100);
        }
        else {
            if(m_altitude < m_newAltitude) {
                setAltitude(m_altitude + 100);
            }
            else if(m_altitude > m_newAltitude) {
                setAltitude(m_altitude - 100);
            }
        }

        m_clocks.m_altitudeClock.restart();
    }
}

void FlyingEntity::updateSpeedData() {
    if(m_newSpeed == m_speed || sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
        return;
    }

    if(m_clocks.m_speedClock.getElapsedTime().asMilliseconds() >= m_clocks.m_speedInterval) {
        if(!hasFuel) {
            setSpeed(m_speed - Utilities::randGen<int>(1, 14));
        }
        else {
            if(m_speed < m_newSpeed) {
                setSpeed(m_speed + 1);
            }
            else if(m_speed > m_newSpeed) {
                setSpeed(m_speed - 1);
            }
        }

        m_clocks.m_speedClock.restart();
    }
}

void FlyingEntity::updateHeadingData() {
    bool shouldUpdateHeading = m_clocks.m_headingClock.getElapsedTime().asMilliseconds() >= m_clocks.m_headingInterval;

    if(!route.empty()) { // if waypoints were given to a flying entity
        setNewHeading(Math::DirectionToPoint(m_entity.getPosition(), route.front().getPosition()));
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && m_heading != m_newHeading && shouldUpdateHeading) {
        if ((m_newHeading - m_heading + 360) % 360 < 180) {
            setHeading(m_heading + 1);
        }
        else {
            setHeading(m_heading - 1);
        }

        m_clocks.m_headingClock.restart();
    }
}

void FlyingEntity::setFallInWeather(int degree) {
    m_fallInWeather = degree;
}

bool FlyingEntity::isInsideScreen() const {
    sf::Vector2f position = m_entity.getPosition();

    return position.x >= -20 && position.x <= 1305 && position.y >= -20 && position.y <= 750;
}

void FlyingEntity::setCrashed() {
    m_isCrashed = true;
}

bool FlyingEntity::getCrashed() const {
    return m_isCrashed;
}

int FlyingEntity::getAltitude() const {
    return m_altitude;
}

sf::Vector2f FlyingEntity::getEntityPosition() const {
    return m_entity.getPosition();
}

std::string FlyingEntity::getArrival() const {
    return m_arrival;
}

int FlyingEntity::getAirspeed() const {
    return m_speed;
}

void FlyingEntity::setEntitySelected() {
    m_entitySelected = true;
    updateText();
}

Waypoint FlyingEntity::getRouteCurrentWaypoint() const {
    if(route.empty()) {
        return {sf::Vector2f(0, 0), ""};
    }
    return route.back();
}

bool FlyingEntity::getIsEntitySelected() const {
    return m_entitySelected;
}

std::string FlyingEntity::getCallsign() const {
    return m_callsign;
}

void FlyingEntity::setFlag(FlyingEntity::Flags flag) {
    m_flags[flag] = true;
}

void FlyingEntity::resetFlag(FlyingEntity::Flags flag) {
    m_flags[flag] = false;
}

bool FlyingEntity::isFlagActive(FlyingEntity::Flags flag) {
    return m_flags[flag];
}