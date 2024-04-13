//
// Created by bgd on 12.04.2024.
//

#include "../header/DataAPI.h"

nlohmann::json DataAPI::getArrivals(const std::string airportICAO)
{
    const std::string link = "https://data.vatsim.net/v3/vatsim-data.json";

    const cpr::Response res = cpr::Get(cpr::Url{link},
                               cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                               cpr::Parameters{{"anon", "true"}, {"key", "value"}});

    nlohmann::json data = nlohmann::json::parse(res.text);
    nlohmann::json arrivals;

    const int pilots_size = data["pilots"].size();

    for(int i = 0; i < pilots_size; i++)
    {
        if(data["pilots"][i]["flight_plan"]["arrival"] == airportICAO)
        {
            arrivals.push_back(data["pilots"][i]);
        }
    }

    return arrivals;
}

std::pair<int, int> DataAPI::getWeather(const std::string airportICAO) {
    const std::string link = "https://aviationweather.gov/api/data/metar?ids=" + airportICAO + "&format=json";
    const cpr::Response res = cpr::Get(cpr::Url{link});

    nlohmann::json metar = nlohmann::json::parse(res.text);

    int wdir = metar[0]["wdir"];
    int wspd = metar[0]["wspd"];

    return {wdir,wspd};
}