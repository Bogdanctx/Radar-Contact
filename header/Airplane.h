//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_AIRPLANE_H
#define OOP_AIRPLANE_H

#include "FlyingEntity.h"
#include <iostream>

class Airplane : public FlyingEntity {
public:
    explicit Airplane(int altitude, int max_altitude, int speed, int max_speed, int heading, int squawk,
                      const std::string &callsign, sf::Vector2f position);
    ~Airplane() { std::cout << "Destr Airplane\n"; }

private:
};


#endif //OOP_AIRPLANE_H
