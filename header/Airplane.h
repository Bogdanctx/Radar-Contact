//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_AIRPLANE_H
#define OOP_AIRPLANE_H

#include "FlyingEntity.h"

class Airplane : public FlyingEntity {
public:
    explicit Airplane(int altitude, int speed, int heading, const std::string& squawk,
                      const std::string &callsign, sf::Vector2f position);
    ~Airplane() = default;

    void update() override;
private:
    void checkAltitudeChange();
    void checkSpeedChange();
    void checkHeadingChange();

    void updateFlightData();

    sf::Clock m_updateAltitudeClock{};
    sf::Clock m_updateSpeedClock{};
    sf::Clock m_updateHeadingClock{};

    sf::Clock m_dataChangeDelay{};

    const int m_updateInterval{};
    const int m_updateAltitudeInterval{};
    const int m_updateSpeedInterval{};
    const int m_updateHeadingInterval{};
};


#endif //OOP_AIRPLANE_H
