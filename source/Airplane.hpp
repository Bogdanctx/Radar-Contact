#pragma once

#include "FlyingEntity.hpp"

class Airplane : public FlyingEntity {
public:
    template <typename... Args>
    explicit Airplane(Args... args) : FlyingEntity(args...) {
        setClocks(Clocks(1100, 750, 800, 160));

        m_minSpeed = 140;
        m_maxSpeed = 335;

        m_minAltitude = 2000;
        m_maxAltitude = 43000;
    }

private:
    void internalUpdate() override;
};
