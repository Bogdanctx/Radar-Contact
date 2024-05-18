//
// Created by bgd on 18.05.2024.
//

#ifndef OOP_UTILS_H
#define OOP_UTILS_H

#include <random>
#include <chrono>
#include <climits>

static std::random_device rd;
static std::mt19937 rng(rd());

int rand32() {
    std::uniform_int_distribution<> uid(INT32_MIN, INT32_MAX);
    return uid(rng);
}

#endif //OOP_UTILS_H
