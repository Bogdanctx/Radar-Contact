#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#define PI 3.14159265

namespace Math
{
    //-----------------------------------------------------------
    // Purpose: Convert radians to degrees
    //-----------------------------------------------------------
    inline float degrees(const float rad) {
        return rad * 180 / PI;
    }

    //-----------------------------------------------------------
    // Purpose: Convert degrees to radians
    //-----------------------------------------------------------
    inline float radians(const float deg) {
        return deg * PI / 180;
    }

    //-----------------------------------------------------------
    // Purpose: Calculate the euclidian distance between 2 points
    //-----------------------------------------------------------
    inline int DistanceBetweenTwoPoints(const sf::Vector2f A, const sf::Vector2f B) {
        float xSquare = (B.x - A.x) * (B.x - A.x);
        float ySquare = (B.y - A.y) * (B.y - A.y);

        float distance = std::sqrt(xSquare + ySquare);

        return static_cast<int>(distance);
    }


    //-----------------------------------------------------------
    // Purpose: Calculate a flying entitie's speed based on altitude
    //-----------------------------------------------------------
    // f(altitude) = 1 / 250 * altitude + 165; -> this function returns what airspeed an airplane should have
    // at {altitude} altitude
    inline int AirspeedAtAltitude(const int altitude) {
        const double a = 1.f / 250.f;
        const double b = 165;

        const double airspeed = a * altitude + b;

        return static_cast<int>(airspeed);
    }

    //-----------------------------------------------------------
    // Purpose: Calculate the direction from origin to point
    //-----------------------------------------------------------
    inline int DirectionToPoint(const sf::Vector2f origin, const sf::Vector2f point) {
        const auto dir_radians = atan2(origin.y - point.y, origin.x - point.x);
        int direction = static_cast<int>(degrees(static_cast<float>(dir_radians)) - 90);

        if(direction < 0) {
            direction += 360;
        }

        return direction;
    }

    //-----------------------------------------------------------
    // Purpose: Calculate the new position of an entity based on
    // speed and direction
    //-----------------------------------------------------------
    inline sf::Vector2f TranslatePositionToPoint(float speed, float direction) {
        return {std::sin(radians(direction)) * speed / 100, std::cos(radians( direction + 180)) * speed / 100};
    }

    //-----------------------------------------------------------
    // Purpose: Used to calculate (X,Y) position based on longitude and latitude
    //-----------------------------------------------------------
    // https://stackoverflow.com/questions/41557891/convert-lat-long-to-x-y-position-within-a-bounding-box
    inline sf::Vector2f MercatorProjection(float crtLatitude, float crtLongitude, const std::vector<float> &imgBounds) {
        const double north = radians(imgBounds[0]);
        const double south = radians(imgBounds[2]);
        const double east = radians(imgBounds[1]);
        const double west = radians(imgBounds[3]);

        const double map_width = 1280;
        const double map_height = 720;

        crtLatitude = radians(crtLatitude);
        crtLongitude = radians(crtLongitude);

        const double ymin = std::log(std::tan(south / 2 + PI / 4));
        const double ymax = std::log(std::tan(north / 2 + PI / 4));

        const double x_factor = map_width / (east - west);
        const double y_factor = map_height / (ymax - ymin);

        const double x = (crtLongitude - west) * x_factor;
        const double y = (ymax - std::log(std::tan(crtLatitude / 2 + PI / 4))) * y_factor;

        return {static_cast<float>(x), static_cast<float>(y)};
    }
}
