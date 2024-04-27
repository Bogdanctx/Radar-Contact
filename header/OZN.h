//
// Created by bgd on 27.04.2024.
//

#ifndef OOP_OZN_H
#define OOP_OZN_H

#include "SpaceEntity.h"

class OZN : public SpaceEntity {
public:
    template <typename... Args> explicit OZN(Args... args) : SpaceEntity(args...) {}
};


#endif //OOP_OZN_H