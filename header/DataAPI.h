//
// Created by bgd on 12.04.2024.
//

#ifndef OOP_DATAAPI_H
#define OOP_DATAAPI_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ResourcesManager.h"

class DataAPI {
public:
    DataAPI() = default;
    ~DataAPI() = default;

    static nlohmann::json getArrivals(const std::string &airportICAO);
    static std::pair<int, int> getWeather(const std::string &airportICAO);
    static std::string getWeatherPath();
private:

};


#endif //OOP_DATAAPI_H
