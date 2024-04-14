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

#include <iostream>
std::vector<sf::Texture> DataAPI::getWeatherTiles(const std::vector<std::pair<float, float>> positions) {
    std::vector<sf::Texture> response;
    sf::Http http{"http://tilecache.rainviewer.com"};
    sf::Http::Request request;
    sf::Http::Response api_response;

    request.setMethod(sf::Http::Request::Post);
    request.setHttpVersion(1, 1);
    request.setField("Content-Type", "application/x-www-form-urlencoded");

    for(const std::pair<float, float> &position: positions) {
        sf::Texture temp_texture;
        const std::string link = "/v2/radar/nowcast_a65885cf5a7d/512/6/" + std::to_string(position.first) + '/' + std::to_string(position.second) + "/1/1_0.png";
        std::cout<<link<<'\n';
        std::cout.flush();
        request.setUri(link);

        api_response = http.sendRequest(request);

        temp_texture.loadFromMemory(api_response.getBody().data(), api_response.getBody().size());

        response.push_back(temp_texture);
    }

    return response;
}