//
// Created by bgd on 22.04.2024.
//

#ifndef OOP_HOTAIRBALLOON_H
#define OOP_HOTAIRBALLOON_H

#include "FlyingEntity.h"

class HotAirBalloon : public FlyingEntity {
public:
    template <typename... Args>
    explicit HotAirBalloon(Args... args) : FlyingEntity(args...) {
        setSpeedConstraints(25, 100);
        setAltitudeConstraints(300, 2700);
        setClocks(Clocks(900, 1300, 850, 310));
    }

    FlyingEntity* clone() const override {
        return new HotAirBalloon(*this);
    }

    void render(sf::RenderWindow *game_window) override;
private:
    void internalUpdate() override;
};


#endif //OOP_HOTAIRBALLOON_H
