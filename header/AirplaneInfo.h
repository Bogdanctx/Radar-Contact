//
// Created by bgd on 14.06.2024.
//

#ifndef OOP_AIRPLANEINFO_H
#define OOP_AIRPLANEINFO_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "FlyingEntity.h"
#include "ResourcesManager.h"

class AirplaneInfo {
public:
    AirplaneInfo(const std::string& strFormat, std::shared_ptr<FlyingEntity>& flyingEntity, int offset);

    void draw(sf::RenderWindow* window);

    std::shared_ptr<FlyingEntity> getFlyingEntityPtr() {
        return flyingEntityPtr;
    }

    sf::RectangleShape getBody() {
        return m_body;
    }

    friend void swap(AirplaneInfo& obj1, AirplaneInfo& obj2) {
        using std::swap;

        swap(obj1.flyingEntityPtr, obj2.flyingEntityPtr);
    }

private:
    sf::RectangleShape m_body{};
    sf::Text m_text;
    std::string m_info{};
    std::shared_ptr<FlyingEntity> flyingEntityPtr{};
};


#endif //OOP_AIRPLANEINFO_H
