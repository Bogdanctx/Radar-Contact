#ifndef OOP_UTILS_H
#define OOP_UTILS_H

#include <random>
#include <chrono>

class Utilities {
public:
    template<typename T>
    static T randGen(T minVal, T maxVal) {
        T randomNumber = 0;

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

    class OneDecimalFloatingPoint { // 1 decimal floating point because std::to_string cannot be formated
        int m_integer;
        int m_fractional;

        public:
            OneDecimalFloatingPoint(int integer, int fractional) : m_integer(integer), m_fractional(fractional) {}

            OneDecimalFloatingPoint& operator--() {
                if(m_fractional == 0) {
                    m_integer--;
                    m_fractional = 9;
                }
                else {
                    m_fractional--;
                }
                return *this;
            }

            bool operator==(const OneDecimalFloatingPoint& other) const {
                return m_integer == other.m_integer && m_fractional == other.m_fractional;
            }
            bool operator<=(const OneDecimalFloatingPoint& other) const {
                return m_integer <= other.m_integer && m_fractional <= other.m_fractional;
            }

            [[nodiscard]] std::string asString() const {
                return std::to_string(m_integer) + ',' + std::to_string(m_fractional);
            }
    };

private:
    static std::random_device rd;
    static std::mt19937 rng;
};

#endif //OOP_UTILS_H
