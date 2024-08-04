#pragma once

#include <random>
#include <chrono>

class Utilities {
public:
    template<typename T>
    static T randGen(T minVal, T maxVal) {
        T randomNumber = 0;

        if(std::is_integral_v<T>) {
            std::uniform_int_distribution<> uid(minVal, maxVal);
            randomNumber = uid(rng);
        }
        else if(std::is_floating_point_v<T>) {
            std::uniform_real_distribution<> urd(minVal, maxVal);
            randomNumber = urd(rng);
        }

        return randomNumber;
    }

private:
    static std::random_device rd;
    static std::mt19937 rng;
};