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
            m_updateAltitudeInterval{1300},
            m_updateSpeedInterval{850},
            m_updateHeadingInterval{310} {}
    FlyingEntity* clone() const override {
        return new HotAirBalloon(*this);
    }

    void render(sf::RenderWindow *game_window) override;
    void update() override;
private:
    int m_updateInterval{};
    int m_updateAltitudeInterval{};
    int m_updateSpeedInterval{};
    int m_updateHeadingInterval{};

    sf::Clock m_updatePositionInterval{};
};


#endif //OOP_HOTAIRBALLOON_H
