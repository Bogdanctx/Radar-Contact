#pragma once

//-----------------------------------------------------------
// Purpose: Used to create numbers with 1 decimal and output them
// because std::to_string takes multiple decimals
//-----------------------------------------------------------
class OneDecimalFloatingPoint {
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
        if(m_integer < other.m_integer)
        {
            return true;
        }
        return m_integer == other.m_integer && m_fractional <= other.m_fractional;
    }

    [[nodiscard]] std::string asString() const {
        return std::to_string(m_integer) + ',' + std::to_string(m_fractional);
    }
};