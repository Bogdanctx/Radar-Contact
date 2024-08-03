#ifndef OOP_MATH_H
#define OOP_MATH_H

#endif //OOP_MATH_H

#include <SFML/Graphics.hpp>

#include <cmath>

class Math
{
public:
    static int DirectionToPoint(sf::Vector2f origin, sf::Vector2f point);
    static sf::Vector2f TranslatePositionToPoint(float speed, float direction);
    static sf::Vector2f MercatorProjection(float crtLatitude, float crtLongitude, const std::vector<float> &imgBounds);
    static int DistanceBetweenTwoPoints(sf::Vector2f A, sf::Vector2f B);
    static int AirspeedAtAltitude(int altitude);

private:
    constexpr static const float PI = 3.1415f;

private:
    static float degrees(float rad); // convert from radians to degrees
    static float radians(float deg); //  convert from degrees to radians
};