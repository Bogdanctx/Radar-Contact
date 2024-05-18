//
// Created by bgd on 20.04.2024.
//

#ifndef RADAR_CONTACT_HELICOPTER_H
#define RADAR_CONTACT_HELICOPTER_H

#include "FlyingEntity.h"

class Helicopter : public FlyingEntity {
public:
    template <typename... Args>
    explicit Helicopter(Args... args) : FlyingEntity(args...) {
        setSpeedConstraints(120, 270);
        setAltitudeConstraints(5000, 17000);
        setClocks(Clocks(600, 750, 680, 70));
    }

    FlyingEntity* clone() const override {
        return new Helicopter(*this);
    }

    void render(sf::RenderWindow *game_window) override;
private:
    void internalUpdate() override;
};

#endif //RADAR_CONTACT_HELICOPTER_H
