//
// Created by bgd on 11.04.2024.
//

#include "../header/Airplane.h"
#include "../header/Math.h"

Airplane::Airplane(int altitude, int speed, int heading, std::string squawk,
                   const std::string &callsign, sf::Vector2f position) :
        FlyingEntity(altitude, speed, heading, squawk, callsign, position)
{

}