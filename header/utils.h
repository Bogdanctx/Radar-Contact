//
// Created by bgd on 18.05.2024.
//

#ifndef OOP_UTILS_H
#define OOP_UTILS_H

#include <random>
#include <chrono>

class Utilities {
public:
    template<typename T>
    static T randGen(T minVal, T maxVal) {
        T randomNumber;

        if(std::is_integral<T>::value) {
            std::uniform_int_distribution<> uid(minVal, maxVal);
            randomNumber = uid(rng);
        }
        else if(std::is_floating_point<T>::value) {
            std::uniform_real_distribution<> urd(minVal, maxVal);
            randomNumber = urd(rng);
        }

        return randomNumber;
    }
private:
    static std::random_device rd;
    static std::mt19937 rng;
};

std::random_device Utilities::rd;
std::mt19937 Utilities::rng(rd());

#endif //OOP_UTILS_H
