//
// Created by bgd on 22.04.2024.
//

#ifndef OOP_HOTAIRBALLOON_H
#define OOP_HOTAIRBALLOON_H

#include "FlyingEntity.h"

class HotAirBalloon : public FlyingEntity {
public:
    template <typename... Args> explicit HotAirBalloon(Args... args) :
            FlyingEntity(args...),
            m_updateInterval{900},
            m_updateAltitudeInterval{970},
            m_updateSpeedInterval{600},
            m_updateHeadingInterval{280} {}

    void update() override;
private:
    int m_updateInterval{};
    int m_updateAltitudeInterval{};
    int m_updateSpeedInterval{};
    int m_updateHeadingInterval{};

    sf::Clock m_updatePositionInterval{};
};


#endif //OOP_HOTAIRBALLOON_H
