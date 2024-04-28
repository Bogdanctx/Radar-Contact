//
// Created by bgd on 27.04.2024.
//

#ifndef OOP_SPACEENTITY_H
#define OOP_SPACEENTITY_H

#include "FlyingEntity.h"

class SpaceEntity : public FlyingEntity {
public:
    SpaceEntity() = default;
    template <typename... Args> explicit SpaceEntity(Args... args) :
            FlyingEntity(args...),
            m_updateInterval{15} {}
    FlyingEntity* clone() const override {
        return new SpaceEntity(*this);
    }

    void render(sf::RenderWindow *game_window) override;
    void update() override;
    void handleEvent(sf::Event game_event, sf::Vector2f mouse_position) override;

    bool isInsideScreen() const;
protected:
    sf::Clock m_updatePositionInterval{};
    int m_updateInterval{};
};


#endif //OOP_SPACEENTITY_H
