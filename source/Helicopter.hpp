#pragma once

#include "FlyingEntity.hpp"

class Helicopter : public FlyingEntity {
public:
    template <typename... Args>
    explicit Helicopter(Args... args) : FlyingEntity(args...) {
        m_updateTimer.interval = 600;
        m_altitudeTimer.interval = 750;
        m_speedTimer.interval = 680;
        m_headingTimer.interval = 70;

        m_minSpeed = 120;
        m_maxSpeed = 270;

        m_minAltitude = 2000;
        m_maxAltitude = 17000;
    }

private:
    void internalUpdate() override;
};

