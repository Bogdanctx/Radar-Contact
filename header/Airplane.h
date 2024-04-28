//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_AIRPLANE_H
#define OOP_AIRPLANE_H

#include "FlyingEntity.h"

class Airplane : public FlyingEntity {
public:
    template <typename... Args> explicit Airplane(Args... args) :
            FlyingEntity(args...),
            m_updateInterval{1100},
            m_updateAltitudeInterval{900},
            m_updateSpeedInterval{800},
            m_updateHeadingInterval{190}
    {
        setSpeedConstraints(185, 335);
        setAltitudeConstraints(5000, 39000);
    }

    FlyingEntity* clone() const override {
        return new Airplane(*this);
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


#endif //OOP_AIRPLANE_H
