#ifndef OOP_HOTAIRBALLOON_H
#define OOP_HOTAIRBALLOON_H

#include "FlyingEntity.h"

class HotAirBalloon : public FlyingEntity {
public:
    template <typename... Args>
    explicit HotAirBalloon(Args... args) : FlyingEntity(args...) {
        setSpeedConstraints(50, 130);
        setAltitudeConstraints(300, 2700);
        setClocks(Clocks(900, 1300, 850, 310));
    }

private:
    void internalUpdate() override;
};


#endif //OOP_HOTAIRBALLOON_H
