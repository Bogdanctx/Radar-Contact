#ifndef RADAR_CONTACT_HELICOPTER_H
#define RADAR_CONTACT_HELICOPTER_H

#include "FlyingEntity.h"

class Helicopter : public FlyingEntity {
public:
    template <typename... Args>
    explicit Helicopter(Args... args) : FlyingEntity(args...) {
        setSpeedConstraints(120, 270);
        setAltitudeConstraints(2000, 17000);
        setClocks(Clocks(600, 750, 680, 70));
    }

private:
    void internalUpdate() override;
    void hijackUpdateData() override;
};

#endif //RADAR_CONTACT_HELICOPTER_H
