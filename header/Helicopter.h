//
// Created by bgd on 20.04.2024.
//

#ifndef RADAR_CONTACT_HELICOPTER_H
#define RADAR_CONTACT_HELICOPTER_H

#include "FlyingEntity.h"

class Helicopter : public FlyingEntity {
public:
    template <typename... Args>
    explicit Helicopter(Args... args) :
                FlyingEntity(args...),
                m_updateInterval{600},
                m_updateAltitudeInterval{750},
                m_updateSpeedInterval{680},
                m_updateHeadingInterval{70}
    {
        setSpeedConstraints(120, 270);
        setAltitudeConstraints(5000, 17000);
    }

    FlyingEntity* clone() const override {
        return new Helicopter(*this);
    }

    void render(sf::RenderWindow *game_window) override;
    void update(bool force) override;
private:
    int m_updateInterval{};
    int m_updateAltitudeInterval{};
    int m_updateSpeedInterval{};
    int m_updateHeadingInterval{};

    sf::Clock m_updatePositionInterval{};
};

#endif //RADAR_CONTACT_HELICOPTER_H
