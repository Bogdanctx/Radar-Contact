#pragma once

#include <random>

namespace Utility
{
    inline int randomNumber(int minVal, int maxVal)
    {
        std::random_device rd;
        std::mt19937 rng(rd());

        std::uniform_int_distribution<> uid(minVal, maxVal);
        int number = uid(rng);

        return number;
    }

    inline double randomNumber(double minVal, double maxVal)
    {
        std::random_device rd;
        std::mt19937 rng(rd());

        std::uniform_real_distribution<> urd(minVal, maxVal);
        double number = urd(rng);

        return number;
    }

    struct Timer {
        Timer() = default;
        explicit Timer(double miliseconds) : interval(miliseconds) {}

        [[nodiscard]] bool passedDelay() const {
            return clock.getElapsedTime().asMilliseconds() >= interval;
        }
        void restart() {
            clock.restart();
        }

        sf::Clock clock;
        double interval = 0;
    };
}