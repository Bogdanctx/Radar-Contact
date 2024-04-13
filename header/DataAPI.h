//
// Created by bgd on 12.04.2024.
//

#ifndef OOP_DATAAPI_H
#define OOP_DATAAPI_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <iostream>

class DataAPI {
public:
    DataAPI() = default;
    ~DataAPI() = default;

    static nlohmann::json getArrivals(const std::string airportICAO);
private:

};


#endif //OOP_DATAAPI_H
