//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_AIRPLANE_H
#define OOP_AIRPLANE_H

#include "FlyingEntity.h"

class Airplane : public FlyingEntity {
public:
    template <typename... Args>
    explicit Airplane(Args... args) : FlyingEntity(args...) {
        setSpeedConstraints(185, 335);
        setAltitudeConstraints(5000, 39000);
        setClocks(Clocks(1100, 900, 800, 190));
    }

    FlyingEntity* clone() const override {
        return new Airplane(*this);
    }

    void render(sf::RenderWindow *game_window) override;

private:
    void internalUpdate() override;
};


#endif //OOP_AIRPLANE_H
