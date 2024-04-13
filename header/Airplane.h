//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_AIRPLANE_H
#define OOP_AIRPLANE_H

#include "FlyingEntity.h"
#include "ResourcesManager.h"
#include <iostream>

class Airplane : public FlyingEntity {
public:
    explicit Airplane(int altitude, int speed, int heading, std::string squawk,
                      const std::string &callsign, sf::Vector2f position, ResourcesManager *resourcesManager);
    ~Airplane() { std::cout << "Destr Airplane\n"; }

private:
    ResourcesManager *m_resourcesManager;
};


#endif //OOP_AIRPLANE_H
