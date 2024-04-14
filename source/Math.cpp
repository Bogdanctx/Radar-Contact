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

// https://stackoverflow.com/questions/2103924/mercator-longitude-and-latitude-calculations-to-x-and-y-on-a-cropped-map-of-the/10401734#10401734
// https://stackoverflow.com/questions/41557891/convert-lat-long-to-x-y-position-within-a-bounding-box NOW
sf::Vector2f Math::MercatorProjection(float crtLatitude, float crtLongitude, std::vector<float> imgBounds,
                                      std::pair<int, int> gameResolution)
{
    const float north = radians(imgBounds[0]);
    const float south = radians(imgBounds[2]);
    const float east = radians(imgBounds[1]);
    const float west = radians(imgBounds[3]);

    const float map_width = gameResolution.first;
    const float map_height = gameResolution.second;

    crtLatitude = radians(crtLatitude);
    crtLongitude = radians(crtLongitude);

    const float ymin = log(tan(south / 2 + PI / 4));
    const float ymax = log(tan(north / 2 + PI / 4));

    const float x_factor = map_width / (east - west);
    const float y_factor = map_height / (ymax - ymin);

    const float x = (crtLongitude - west) * x_factor;
    const float y = (ymax - log(tan(crtLatitude / 2 + PI / 4))) * y_factor;

    return {x,y};
}