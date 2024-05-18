//
// Created by bgd on 18.05.2024.
//

#include "../header/MockAPI.h"

#include <fstream>

nlohmann::json MockAPI::getArrivals() {
    std::ifstream f("../resources/mock_api/vatsim-data.json");

    nlohmann::json data = nlohmann::json::parse(f);

    return data;
}

std::string MockAPI::getWeatherPath() {
    std::ifstream f("../resources/mock_api/weahter-maps.json");

    nlohmann::json data = nlohmann::json::parse(f);

    return data["radar"]["nowcast"].back()["path"];
}