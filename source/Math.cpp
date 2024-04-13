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
sf::Vector2f Math::MercatorProjection(float crtLatitude, float crtLongitude, std::vector<float> imgBounds,
                                      std::pair<int, int> gameResolution) {

    const float mapWidth = gameResolution.first;
    const float mapHeight = gameResolution.second;

    const float mapLonLeft = imgBounds[3];
    const float mapLonRight = imgBounds[1];
    const float mapLonDelta = mapLonRight - mapLonLeft;

    const float mapLatBottom = imgBounds[2];
    const float mapLatBottomDegree = radians(mapLatBottom);

    const float x = (crtLongitude - mapLonLeft) * (mapWidth / mapLonDelta);

    crtLatitude = radians(crtLatitude);

    const float worldMapWidth = ((mapWidth / mapLonDelta) * 360) / (2 * PI);
    const float mapOffsetY = (worldMapWidth / 2 * log((1+sin(mapLatBottomDegree)) / (1 - sin(mapLatBottomDegree))));
    const float y = mapHeight - ((worldMapWidth / 2 * log((1 + sin(crtLatitude)) / (1 - sin(crtLatitude)))) - mapOffsetY);

    return {x,y};
}