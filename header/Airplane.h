//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_AIRPLANE_H
#define OOP_AIRPLANE_H

#include "FlyingEntity.h"

class Airplane : public FlyingEntity {
public:
    explicit Airplane(int altitude, int speed, int heading, const std::string& squawk,
                      const std::string &callsign, sf::Vector2f position, const std::string &arrival);
    virtual ~Airplane() = default;

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


#endif //OOP_AIRPLANE_H
