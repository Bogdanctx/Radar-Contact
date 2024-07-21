#ifndef RADAR_CONTACT_HELICOPTER_H
#define RADAR_CONTACT_HELICOPTER_H

#include "FlyingEntity.h"

class Helicopter : public FlyingEntity {
public:
    template <typename... Args>
    explicit Helicopter(Args... args) : FlyingEntity(args...) {
        setClocks(Clocks(600, 750, 680, 70));

        m_minSpeed = 120;
        m_maxSpeed = 270;

        m_minAltitude = 2000;
        m_maxAltitude = 17000;
    }

private:
    void internalUpdate() override;
};

#endif //RADAR_CONTACT_HELICOPTER_H
