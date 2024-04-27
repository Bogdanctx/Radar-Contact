//
// Created by bgd on 27.04.2024.
//

#ifndef OOP_OZN_H
#define OOP_OZN_H

#include "FlyingEntity.h"

class OZN : public FlyingEntity {
public:
    template <typename... Args> explicit OZN(Args... args) :
            FlyingEntity(args...),
            m_updateInterval{13},
            m_updateAltitudeInterval{750},
            m_updateSpeedInterval{680},
            m_updateHeadingInterval{70} {}
    FlyingEntity* clone() const override {
        return new OZN(*this);
    }

    void render(sf::RenderWindow *game_window) override;
    void update() override;
    void handleEvent(sf::Event game_event, sf::Vector2f mouse_position) override;

private:
    int m_updateInterval{};
    int m_updateAltitudeInterval{};
    int m_updateSpeedInterval{};
    int m_updateHeadingInterval{};

    sf::Clock m_updatePositionInterval{};
};


#endif //OOP_OZN_H