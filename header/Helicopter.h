//
// Created by bgd on 20.04.2024.
//

#ifndef RADAR_CONTACT_HELICOPTER_H
#define RADAR_CONTACT_HELICOPTER_H

#include "FlyingEntity.h"


class Helicopter : public FlyingEntity {
public:
    explicit Helicopter(int altitude, int speed, int heading, const std::string& squawk,
               const std::string &callsign, sf::Vector2f position, const std::string &arrival);
    virtual ~Helicopter() = default;

    void update() override;
private:
    void updateFlightData();

    sf::Clock m_updateAltitudeClock{};
    sf::Clock m_updateSpeedClock{};
    sf::Clock m_updateHeadingClock{};

    int m_updateInterval{};
    int m_updateAltitudeInterval{};
    int m_updateSpeedInterval{};
    int m_updateHeadingInterval{};
};


#endif //RADAR_CONTACT_HELICOPTER_H
