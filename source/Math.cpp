#include "Math.hpp"

//-----------------------------------------------------------
// Purpose: Calculate the euclidian distance between 2 points
//-----------------------------------------------------------
int Math::DistanceBetweenTwoPoints(const sf::Vector2f A, const sf::Vector2f B) {
    float xSquare = (B.x - A.x) * (B.x - A.x);
    float ySquare = (B.y - A.y) * (B.y - A.y);

    float distance = std::sqrt(xSquare + ySquare);

    return (int) distance;
}


//-----------------------------------------------------------
// Purpose: Calculate a flying entitie's speed based on altitude
//-----------------------------------------------------------
// f(altitude) = 1 / 250 * altitude + 165; -> this function returns what airspeed an airplane should have
// at {altitude} altitude
int Math::AirspeedAtAltitude(const int altitude) {
    const double a = 1.f / 250.f;
    const double b = 165;

    const double airspeed = a * altitude + b;

    return static_cast<int>(airspeed);
}

//-----------------------------------------------------------
// Purpose: Calculate the direction from origin to point
//-----------------------------------------------------------
int Math::DirectionToPoint(const sf::Vector2f origin, const sf::Vector2f point) {
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
sf::Vector2f Math::TranslatePositionToPoint(float speed, float direction) {
    sf::Vector2f p{
        std::sin(radians(direction)) * speed / 100,
        std::cos(radians( direction + 180)) * speed / 100
    };

    return p;
}

//-----------------------------------------------------------
// Purpose: Convert radians to degrees
//-----------------------------------------------------------
float Math::degrees(const float rad) {
    return rad * 180 / PI;
}

//-----------------------------------------------------------
// Purpose: Convert degrees to radians
//-----------------------------------------------------------
float Math::radians(const float deg) {
    return deg * PI / 180;
}

//-----------------------------------------------------------
// Purpose: Used to calculate (X,Y) position based on longitude and latitude
//-----------------------------------------------------------
// https://stackoverflow.com/questions/41557891/convert-lat-long-to-x-y-position-within-a-bounding-box
sf::Vector2f Math::MercatorProjection(float crtLatitude, float crtLongitude, const std::vector<float> &imgBounds) {
    const float north = radians(imgBounds[0]);
    const float south = radians(imgBounds[2]);
    const float east = radians(imgBounds[1]);
    const float west = radians(imgBounds[3]);

    const float map_width = 1280;
    const float map_height = 720;

    crtLatitude = radians(crtLatitude);
    crtLongitude = radians(crtLongitude);

    const float ymin = std::log(std::tan(south / 2 + PI / 4));
    const float ymax = std::log(std::tan(north / 2 + PI / 4));

    const float x_factor = map_width / (east - west);
    const float y_factor = map_height / (ymax - ymin);

    const float x = (crtLongitude - west) * x_factor * 0.998f;
    const float y = (ymax - std::log(std::tan(crtLatitude / 2 + PI / 4))) * y_factor * 0.995f;

    return {x,y};
}