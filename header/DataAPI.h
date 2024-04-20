//
// Created by bgd on 12.04.2024.
//

#ifndef OOP_DATAAPI_H
#define OOP_DATAAPI_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <unordered_set>

#include "ResourcesManager.h"

class DataAPI {
public:
    DataAPI() = default;
    ~DataAPI() = default;

    nlohmann::json getArrivals(const std::string &region);
    static std::string getWeatherPath();
private:
    std::unordered_set<std::string> m_fetchedEntities;
};


#endif //OOP_DATAAPI_H
