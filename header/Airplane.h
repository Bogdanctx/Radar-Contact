//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_AIRPLANE_H
#define OOP_AIRPLANE_H

#include "FlyingEntity.h"

class Airplane : public FlyingEntity {
public:
    template <typename... Args> explicit Airplane(Args... args) :
            FlyingEntity(args...),
            m_updateInterval{1100},
            m_updateAltitudeInterval{900},
            m_updateSpeedInterval{800},
            m_updateHeadingInterval{190} {}

    void update() override;
private:
    int m_updateInterval{};
    int m_updateAltitudeInterval{};
    int m_updateSpeedInterval{};
    int m_updateHeadingInterval{};

    sf::Clock m_updatePositionInterval{};
};


#endif //OOP_AIRPLANE_H
