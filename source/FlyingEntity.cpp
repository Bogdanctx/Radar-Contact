#include "FlyingEntity.hpp"
#include "Math.hpp"
#include "ResourcesManager.hpp"

FlyingEntity::FlyingEntity(int altitude, int speed, int heading, const std::string &squawk, const std::string &callsign,
                           sf::Vector2f position, const std::string &arrival) :
        m_callsignText{ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), callsign, 10},
        m_heading{heading}, m_speed{speed},
        m_altitude{altitude},
        m_newHeading{heading},
        m_newAltitude{altitude},
        m_newSpeed{speed},
        m_arrival{arrival},
        m_arrivalText{ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), arrival, 10},
        m_squawk{squawk},
        m_squawkText(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), squawk, 10),
        m_routeWaypointsText{ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), "", 10},
        m_headingText{ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), std::to_string(heading), 10},
        m_speedText{ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), std::to_string(speed), 10},
        m_altitudeText{ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), std::to_string(altitude), 10},
        m_fuelText{ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), m_fuel.asString(), 10},
        m_newHeadingText{ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), std::to_string(m_newHeading), 10},
        m_newSpeedText{ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), std::to_string(speed), 10},
        m_newAltitudeText{ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), std::to_string(altitude), 10},
        m_callsign{callsign},
        m_headingStick{sf::Vector2f(26, 1.2f)}
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
    m_headingStick.setRotation(sf::Angle(sf::degrees(heading - 90)));

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

//-----------------------------------------------------------
// Purpose: Update flying entities data (heading, altitude, fuel, etc.) if it is selected
// or just update the position callsign
//-----------------------------------------------------------
void FlyingEntity::updateText() {
    if(!m_isEntitySelected) {
        const sf::Vector2f position = m_entity.getPosition();
        m_callsignText.setPosition(sf::Vector2f(position.x - 5, position.y - 20));
        return;
    }

    const sf::Vector2f position = m_entity.getPosition();

    m_callsignText.setPosition(sf::Vector2f(position.x - 8, position.y - 30));

    float xOffset = position.x - 8 + m_callsignText.getLocalBounds().size.x + 5;
    m_squawkText.setPosition(sf::Vector2f(xOffset, position.y - 30));
    xOffset += m_squawkText.getLocalBounds().size.x + 5;
    m_arrivalText.setPosition(sf::Vector2f(xOffset, position.y - 30));

    xOffset += m_arrivalText.getLocalBounds().size.x + 5;
    m_routeWaypointsText.setPosition(sf::Vector2f(xOffset, position.y - 30));

    xOffset = position.x - 8;
    m_fuelText.setPosition(sf::Vector2f(xOffset, position.y - 20));

    xOffset += m_fuelText.getLocalBounds().size.x + 5;
    m_speedText.setPosition(sf::Vector2f(xOffset, position.y - 20));

    xOffset += m_speedText.getLocalBounds().size.x + 5;
    m_headingText.setPosition(sf::Vector2f(xOffset, position.y - 20));

    xOffset += m_headingText.getLocalBounds().size.x + 5;
    m_altitudeText.setPosition(sf::Vector2f(xOffset, position.y - 20));

    xOffset += m_altitudeText.getLocalBounds().size.x + 5;
    m_newSpeedText.setPosition(sf::Vector2f(xOffset, position.y - 20));

    xOffset += m_newSpeedText.getLocalBounds().size.x + 5;
    m_newHeadingText.setPosition(sf::Vector2f(xOffset, position.y - 20));

    xOffset += m_newHeadingText.getLocalBounds().size.x + 5;
    m_newAltitudeText.setPosition(sf::Vector2f(xOffset, position.y - 20));

    m_headingStick.setPosition(sf::Vector2f(position.x, position.y));
}

//-----------------------------------------------------------
// Purpose: Draw flying entity body, callsign, airspeed, altitude, etc.
//-----------------------------------------------------------
void FlyingEntity::render(sf::RenderWindow* gameWindow) {
    gameWindow->draw(m_entity);
    gameWindow->draw(m_callsignText);

    if(m_isEntitySelected) {
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

void FlyingEntity::handleEvent(const std::optional<sf::Event>& event, const sf::Vector2f mousePosition) {
    if(event->is<sf::Event::MouseButtonPressed>())
    {
        sf::FloatRect entityBounds = m_entity.getGlobalBounds();

        // if an entity has been selected by user
        if(entityBounds.contains(mousePosition)) {
            m_isEntitySelected = true;
            updateText();
        }
        else {
            m_isEntitySelected = false;
            updateText();
        }
    }
    else if(event->is<sf::Event::MouseWheelScrolled>())
    {
        if(m_isEntitySelected) {
            float delta = event->getIf<sf::Event::MouseWheelScrolled>()->delta;

            checkAltitudeChange(delta);
            checkSpeedChange(delta);
        }
    }
}

void FlyingEntity::addWaypointToRoute(const Waypoint& waypoint) {
    route.push_back(waypoint);

    m_routeWaypoints += waypoint.getName() + ' ';
    m_routeWaypointsText.setString(m_routeWaypoints);
}

//-----------------------------------------------------------
// Purpose: This function checks if player wants to change the
// altitude of current flying entity by pressing LCTRL
//-----------------------------------------------------------
void FlyingEntity::checkAltitudeChange(int scrollUsed) {
    if(isFlagActive(Flags::LOST_COMMS) || isFlagActive(Flags::HIJACK)) {
        return;
    }

    if(sf::Keyboard::isKeyPressed(m_altitudeButton)) {
        if(m_newAltitude + 100 <= m_maxAltitude && ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_buttonDelayTimer.passedDelay()) || scrollUsed > 0)) {
            setNewAltitude(m_newAltitude + 100);
            m_buttonDelayTimer.restart();
        }
        if(m_newAltitude - 100 >= m_minAltitude && ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_buttonDelayTimer.passedDelay()) || scrollUsed < 0)) {
            setNewAltitude(m_newAltitude - 100);
            m_buttonDelayTimer.restart();
        }
    }
}

OneDecimalFloatingPoint FlyingEntity::getFuel() const
{
    return m_fuel;
}


//-----------------------------------------------------------
// Purpose: This function checks if player wants to change the
// altitude of current flying entity by pressing LCTRL
//-----------------------------------------------------------
void FlyingEntity::checkSpeedChange(int scrollUsed) {
    if(isFlagActive(Flags::LOST_COMMS) || isFlagActive(Flags::HIJACK)) {
        return;
    }

    if(sf::Keyboard::isKeyPressed((m_speedButton))) {
        if(m_newSpeed + 1 <= m_maxSpeed && ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_buttonDelayTimer.passedDelay()) || scrollUsed > 0)) {
            setNewSpeed(m_newSpeed + 1);
            m_buttonDelayTimer.restart();
        }
        if(m_newSpeed - 1 >= m_minSpeed && ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_buttonDelayTimer.passedDelay()) || scrollUsed < 0)) {
            setNewSpeed(m_newSpeed - 1);
            m_buttonDelayTimer.restart();
        }
    }
}

//-----------------------------------------------------------
// Purpose: When a flying entity is hijacked, the heading,
// altitude and airspeed are randomly controlled by hijacker
// (an experienced pilot :) )
//-----------------------------------------------------------
void FlyingEntity::hijackUpdateData() {
    setNewHeading(Utility::randomNumber(0, 360));
    setNewSpeed(Utility::randomNumber(m_minSpeed, m_maxSpeed));
    setNewAltitude(Utility::randomNumber(m_minAltitude, m_maxAltitude) / 100 * 100);
}

//-----------------------------------------------------------
// Purpose: Update flying entity data, variables, etc.
//-----------------------------------------------------------
void FlyingEntity::update(sf::Vector2f mousePosition) {
    m_mousePosition = mousePosition;

    if(m_isEntitySelected) {
        checkAltitudeChange(); // check if user is changing entity altitude
        checkSpeedChange(); // check if user is changing entity speed
        checkHeadingChange(); // check if user is changing entity heading
    }

    updateAltitudeData();
    updateSpeedData();
    updateHeadingData();
    updateFuel();
    updateEntityColor();

    handleSpecialFlightConditions();

    if(m_updateTimer.passedDelay()) {
        internalUpdate();
        adjustFlightParametersBasedOnWeather();

        if(m_altitude <= 0 || m_speed <= m_minSpeed) {
            setCrashed();
        }

        updateText();

        // if no direction is choosen, then heading stick might be updated
        if(!sf::Keyboard::isKeyPressed(m_headingButton)) {
            m_headingStick.setRotation(sf::Angle(sf::degrees(m_heading - 90)));
        }

        if(!route.empty()) {
            sf::Vector2f waypointPosition = route.front().getPosition();
            int distance = Math::DistanceBetweenTwoPoints(m_entity.getPosition(), waypointPosition);

            if(distance <= 5) {
                route.pop_front();
            }
        }
        else {
            m_routeWaypoints.clear();
            m_routeWaypointsText.setString(m_routeWaypoints);
        }

        m_updateTimer.restart();
    }
}

//-----------------------------------------------------------
// Purpose: This function handles the case when the flying
// entity is being hijacked or has lost communication with ATC
//-----------------------------------------------------------
void FlyingEntity::handleSpecialFlightConditions() {
    if(isFlagActive(Flags::HIJACK) && m_hijackTimer.passedDelay()) {
        hijackUpdateData();

        m_hijackTimer.interval = Utility::randomNumber(1400, 2800);
        m_hijackTimer.restart();
    }

    // squawk = 7600 -> lost communications
    if(m_squawk == "7600" && m_lostCommsTimer.passedDelay()) {
        if(isFlagActive(Flags::LOST_COMMS)) {
            resetFlag(Flags::LOST_COMMS);
        }
        else {
            setFlag(Flags::LOST_COMMS);
        }
        m_lostCommsTimer.interval = Utility::randomNumber(9000, 1800);
        m_lostCommsTimer.restart();
    }
}

//-----------------------------------------------------------
// Purpose: When a flying entity is going through storms or
// bad weather, there are turbulences which influence
// speed, heading and altitude
//-----------------------------------------------------------
void FlyingEntity::adjustFlightParametersBasedOnWeather() {
    switch (m_fallInWeather) {
        case Weather::RainDanger::Blue: {
            setAltitude(m_altitude + Utility::randomNumber(-100, 100) / 100 * 100);
            setHeading(m_heading + Utility::randomNumber(-2, 2));
            setSpeed(m_speed + Utility::randomNumber(-2, 2));

            break;
        }
        case Weather::RainDanger::Yellow: {
            setAltitude(m_altitude + Utility::randomNumber(-400, 200) / 100 * 100);
            setHeading(m_heading + Utility::randomNumber(-10, 10));
            setSpeed(m_speed + Utility::randomNumber(-5, 5));

            break;
        }
        case Weather::RainDanger::Red: {
            setAltitude(m_altitude + Utility::randomNumber(-800, 100) / 100 * 100);
            setHeading(m_heading + Utility::randomNumber(-15, 15));
            setSpeed(m_speed + Utility::randomNumber(-10, 10));

            break;
        }
        case Weather::RainDanger::Pink: {
            setAltitude(m_altitude + Utility::randomNumber(-1000, 0) / 100 * 100);
            setHeading(m_heading + Utility::randomNumber(-25, 25));
            setSpeed(m_speed + Utility::randomNumber(-16, 16));

            break;
        }
        default:
            break;
    }
}

//-----------------------------------------------------------
// Purpose: Depending on which flags are active, set flying entitie's
// body color
//-----------------------------------------------------------
void FlyingEntity::updateEntityColor() {
    if(isFlagActive(Flags::DANGER_COLLISION) || isFlagActive(Flags::HIJACK) || isFlagActive(Flags::LOST_COMMS) ||
            isFlagActive(Flags::LOW_FUEL)) {
        m_entity.setFillColor(sf::Color::Red);
    }
    else if(isFlagActive(Flags::WARNING_COLLISION) || isFlagActive(Flags::GENERAL_EMERGENCY)) {
        m_entity.setFillColor(sf::Color(230, 140, 44));
    }
    else {
        m_entity.setFillColor(sf::Color::White);
    }
}

//-----------------------------------------------------------
// Purpose: Used to change the actual speed of the flying entity
//-----------------------------------------------------------
void FlyingEntity::setSpeed(int speed) {
    m_speed = speed;
    m_speedText.setString(std::to_string(m_speed));
}

//-----------------------------------------------------------
// Purpose: Used to change the actual altitude of the flying entity
//-----------------------------------------------------------
void FlyingEntity::setAltitude(int altitude) {
    m_altitude = altitude;
    m_altitudeText.setString(std::to_string(m_altitude));
}

//-----------------------------------------------------------
// Purpose: Used to change the actual heading of the flying entity
// Obs: heading stick rotation must be set manually
//-----------------------------------------------------------
void FlyingEntity::setHeading(int heading) {
    if(heading < 0) {
        heading += 360;
    }
    else if(heading > 360) {
        heading -= 360;
    }

    m_heading = heading;
    m_headingText.setString(std::to_string(m_heading));
}

//-----------------------------------------------------------
// Purpose: Used to let the flying entity know that it must
// achieve a new speed
//-----------------------------------------------------------
void FlyingEntity::setNewSpeed(int newSpeed) {
    m_newSpeed = newSpeed;
    m_newSpeedText.setString(std::to_string(m_newSpeed));
}

//-----------------------------------------------------------
// Purpose: Used to let the flying entity know that it must
// achieve a new altitude
//-----------------------------------------------------------
void FlyingEntity::setNewAltitude(int newAltitude) {
    m_newAltitude = newAltitude;
    m_newAltitudeText.setString(std::to_string(m_newAltitude));
}

//-----------------------------------------------------------
// Purpose: Used to let the flying entity now that it must
// achieve a new heading
// Obs: heading stick rotation must be manually adjusted
//-----------------------------------------------------------
void FlyingEntity::setNewHeading(int newHeading) {
    if(newHeading < 0) {
        newHeading += 360;
    }
    else if(newHeading > 360) {
        newHeading -= 360;
    }

    m_newHeading = newHeading;
    m_newHeadingText.setString(std::to_string(m_newHeading));
}

//-----------------------------------------------------------
// Purpose: This function updates the fuel of a flying entity,
// sets how fast the fuel is consumed and toggles LOW_FUEL flag
//-----------------------------------------------------------
void FlyingEntity::updateFuel() {
    if(!hasFuel) {
        return;
    }

    if(m_fuelConsumptionTimer.passedDelay()) {
        --m_fuel;
        m_fuelText.setString(m_fuel.asString());

        if(m_fuel <= OneDecimalFloatingPoint(2, 5)) {
            setFlag(Flags::LOW_FUEL);
        }

        if(m_fuel <= OneDecimalFloatingPoint(0, 0)) {
            hasFuel = false;
            m_altitude -= 100;
            m_speed--;
        }

        m_fuelConsumptionTimer.restart();
    }

    if (m_speed <= m_newSpeed)
    { // is reducing speed
        if (m_altitude < m_newAltitude)
        { // is descending
            m_fuelConsumptionTimer.interval = 5200; // Less fuel needed when reducing speed and descending
        }
        else
        {
            m_fuelConsumptionTimer.interval = 4300; // Moderate fuel needed when reducing speed and maintaining/climbing
        }
    }
    else
    { // is increasing speed
        if (m_altitude <= m_newAltitude)
        {
            m_fuelConsumptionTimer.interval = 3600; // Moderate fuel needed when increasing speed and descending/maintaining
        }
        else
        {
            m_fuelConsumptionTimer.interval = 2800; // More fuel needed when increasing speed and climbing
        }
    }

    if (m_speed == m_newSpeed && m_altitude == m_newAltitude)
    {
        m_fuelConsumptionTimer.interval = 4000; // Moderate fuel consumption when maintaining speed and altitude
    }
}

//-----------------------------------------------------------
// Purpose: This function checks if player wants to change the
// heading of current flying entity by pressing LSHIFT
// Obs: this function removes the route of a flying entity
//-----------------------------------------------------------
void FlyingEntity::checkHeadingChange() {
    if(isFlagActive(Flags::LOST_COMMS) || isFlagActive(Flags::HIJACK)) {
        return;
    }

    if(sf::Keyboard::isKeyPressed((m_headingButton))) {
        int dir = Math::DirectionToPoint(m_entity.getPosition(), m_mousePosition);
        m_headingStick.setRotation(sf::Angle(sf::degrees(dir - 90)));
        setNewHeading(dir);

        while(!route.empty()) {
            route.pop_front();
        }

        m_routeWaypoints = "";
        m_routeWaypointsText.setString(m_routeWaypoints);
    }
}

//-----------------------------------------------------------
// Purpose: This function returns the clock variable and m_updateInterval
// Obs: Used to check in other files if this flying entity must be
// updated or not
//-----------------------------------------------------------
bool FlyingEntity::canUpdate() const {
    return m_updateTimer.passedDelay();
}

//-----------------------------------------------------------
// Purpose: This function changes the actual altitude of the
// flying entity based on the {newAltitude} value.
//-----------------------------------------------------------
void FlyingEntity::updateAltitudeData() {
    if(sf::Keyboard::isKeyPressed(m_altitudeButton) || m_altitude == m_newAltitude) {
        return;
    }

    if(m_altitudeTimer.passedDelay()) {
        if(!hasFuel) {
            setAltitude(m_altitude - Utility::randomNumber(100, 300) / 100 * 100);
        }
        else {
            if(m_altitude < m_newAltitude) {
                setAltitude(m_altitude + 100);
            }
            else {
                setAltitude(m_altitude - 100);
            }
        }

        m_altitudeTimer.restart();
    }
}

//-----------------------------------------------------------
// Purpose: This function changes the actual speed of the
// flying entity based on the {newSpeed} value.
//-----------------------------------------------------------
void FlyingEntity::updateSpeedData() {
    if(m_newSpeed == m_speed || sf::Keyboard::isKeyPressed(m_speedButton)) {
        return;
    }
    if(!hasFuel) {
        m_speedTimer.interval = 1700;
    }

    if(m_speedTimer.passedDelay()) {
        if(!hasFuel) {

            // slower speed decreasing at high altitudes
            if(m_altitude <= 2000) {
                setSpeed(m_speed - Utility::randomNumber(1, 5));
            }
            else {
                setSpeed(m_speed - 1);
            }

        }
        else {
            if(m_speed < m_newSpeed) {
                setSpeed(m_speed + 1);
            }
            else {
                setSpeed(m_speed - 1);
            }
        }

        m_speedTimer.restart();
    }
}

//-----------------------------------------------------------
// Purpose: This function changes the actual heading of the
// flying entity based on the {newHeading} value.
//-----------------------------------------------------------
void FlyingEntity::updateHeadingData() {
    if(!route.empty()) { // if waypoints were given to a flying entity
        setNewHeading(Math::DirectionToPoint(m_entity.getPosition(), route.front().getPosition()));
    }

    if(!sf::Keyboard::isKeyPressed(m_headingButton) && m_heading != m_newHeading && m_headingTimer.passedDelay()) {
        if ((m_newHeading - m_heading + 360) % 360 < 180) {
            setHeading(m_heading + 1);
        }
        else {
            setHeading(m_heading - 1);
        }

        m_headingTimer.restart();
    }
}

//-----------------------------------------------------------
// Purpose: This function sets the power of turbulences
// when this flying entity is going through storms
//-----------------------------------------------------------
void FlyingEntity::setFallInWeather(int degree) {
    m_fallInWeather = degree;
}

//-----------------------------------------------------------
// Purpose: This function sets the m_isCrashed parameter
// Obs: This is used to erase crashed entities from game
//-----------------------------------------------------------
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

const std::string& FlyingEntity::getArrival() const {
    return m_arrival;
}

int FlyingEntity::getAirspeed() const {
    return m_speed;
}

void FlyingEntity::setEntitySelected() {
    m_isEntitySelected = true;
    updateText();
}

Waypoint FlyingEntity::getRouteCurrentWaypoint() const {
    if(route.empty()) {
        return {sf::Vector2f(0, 0), ""};
    }
    return route.front();
}

bool FlyingEntity::getIsEntitySelected() const {
    return m_isEntitySelected;
}

const std::string& FlyingEntity::getCallsign() const {
    return m_callsign;
}

void FlyingEntity::setFlag(FlyingEntity::Flags flag) {
    m_flags[flag] = true;
}

void FlyingEntity::resetFlag(FlyingEntity::Flags flag) {
    m_flags[flag] = false;
}

bool FlyingEntity::isFlagActive(FlyingEntity::Flags flag) const {
    return m_flags[flag];
}