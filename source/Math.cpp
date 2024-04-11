//
// Created by bgd on 11.04.2024.
//

#include "../header/Math.h"

int  Math::DirectionToPoint(const sf::Vector2f origin, const sf::Vector2f point)
{
    const float dir_radians = atan2(origin.y - point.y, origin.x - point.x);
    int direction = (int) degrees(dir_radians) - 90;

    if(direction < 0) {
        direction += 360;
    }

    return direction;
}

sf::Vector2f Math::TranslatePositionToPoint(const float speed, const float direction)
{
    sf::Vector2f p{
        sin(radians(direction)) * speed / 100,
        cos(radians(direction + 180)) * speed / 100
    };

    return p;
}

float Math::degrees(const float rad)
{
    return rad * 180 / PI;
}

float Math::radians(const float deg)
{
    return deg * PI / 180;
}