//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_MATH_H
#define OOP_MATH_H

#endif //OOP_MATH_H

#include <SFML/Graphics.hpp>
#include <math.h>

class Math
{
public:
    static int DirectionToPoint(sf::Vector2f origin, sf::Vector2f point);
    static sf::Vector2f TranslatePositionToPoint(float speed, float direction);
private:
    constexpr static const float PI = 3.14159265;

    static float degrees(float rad); // conversie din radiani in grade
    static float radians(float deg); //  conversie din grade in radiani
};