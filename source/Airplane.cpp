//
// Created by bgd on 11.04.2024.
//

#include "../header/Airplane.h"

Airplane::Airplane(int altitude, int max_altitude, int speed, int max_speed, int heading, int squawk,
                   const std::string &callsign, sf::Vector2f position)  :
                   FlyingEntity{altitude, max_altitude, speed, max_speed, heading, squawk, callsign, position}
{

}