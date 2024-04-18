//
// Created by bgd on 12.04.2024.
//

#include "../header/DataAPI.h"
#include <iostream>
nlohmann::json DataAPI::getArrivals(const std::string &airportICAO)
{
    const std::string link = "https://data.vatsim.net/v3/vatsim-data.json";

    const cpr::Response res = cpr::Get(cpr::Url{link},
                               cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                               cpr::Parameters{{"anon", "true"}, {"key", "value"}});

    nlohmann::json data = nlohmann::json::parse(res.text);
    nlohmann::json arrivals;

    const int pilots_size = (int) data["pilots"].size();

    for(int i = 0; i < pilots_size; i++)
    {
        int altitude = data["pilots"][i]["altitude"];
        if(data["pilots"][i]["flight_plan"]["arrival"] == airportICAO && altitude >= 10000)
        {
            altitude = altitude / 1000 * 1000;
            data["pilots"][i]["altitude"] = altitude;
            arrivals.push_back(data["pilots"][i]);
        }
    }

    return arrivals;
}

std::pair<int, int> DataAPI::getWeather(const std::string &airportICAO) {
    const std::string link = "https://aviationweather.gov/api/data/metar?ids=" + airportICAO + "&format=json";
    const cpr::Response res = cpr::Get(cpr::Url{link});

    nlohmann::json metar = nlohmann::json::parse(res.text);

    int wdir = metar[0]["wdir"];
    int wspd = metar[0]["wspd"];

    return {wdir,wspd};
}

std::string DataAPI::getWeatherPath() {
    const std::string link = "https://api.rainviewer.com/public/weather-maps.json";
    const cpr::Response res = cpr::Get(cpr::Url{link});

    nlohmann::json api = nlohmann::json::parse(res.text);

    return api["radar"]["nowcast"].back()["path"];
}