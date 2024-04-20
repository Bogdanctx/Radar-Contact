//
// Created by bgd on 12.04.2024.
//

#include "../header/DataAPI.h"
#include "../header/Math.h"

nlohmann::json DataAPI::getArrivals(const std::string &region)
{
    const std::string link = "https://data.vatsim.net/v3/vatsim-data.json";

    const cpr::Response res = cpr::Get(cpr::Url{link},
                               cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                               cpr::Parameters{{"anon", "true"}, {"key", "value"}});

    nlohmann::json data = nlohmann::json::parse(res.text);
    nlohmann::json arrivals;

    const int pilots_size = (int) data["pilots"].size();
    const std::vector<float> longLatBox{ResourcesManager::Instance().getRegionBox(region)};
    const std::unordered_map<std::string, std::pair<int, int>> regionAirports = ResourcesManager::Instance().getRegionAirports(region);

    for(const auto &airport: regionAirports)
    {
        const std::string airportIcao = airport.first;

        for(int i = 0; i < pilots_size; i++)
        {
            if(data["pilots"][i]["flight_plan"]["arrival"] == airportIcao)
            {
                const std::string callsign = data["pilots"][i]["callsign"];

                if(m_fetchedEntities.find(callsign) == m_fetchedEntities.end())
                {
                    int altitude = data["pilots"][i]["altitude"];
                    const float latitude = data["pilots"][i]["latitude"];
                    const float longitude = data["pilots"][i]["longitude"];
                    const sf::Vector2f mercatorProjection = Math::MercatorProjection(latitude, longitude, longLatBox);
                    const int distanceFromMiddle = Math::DistanceBetweenTwoPoints(sf::Vector2f(640, 360), mercatorProjection);

                    if(distanceFromMiddle <= 640 && altitude >= 2000 && altitude <= 40000) {
                        altitude = altitude / 1000 * 1000;
                        data["pilots"][i]["altitude"] = altitude;
                        data["pilots"][i]["longitude"] = mercatorProjection.x;
                        data["pilots"][i]["latitude"] = mercatorProjection.y;

                        m_fetchedEntities.insert(callsign);
                        arrivals.push_back(data["pilots"][i]);
                    }
                }

            }
        }
    }

    return arrivals;
}

/*std::pair<int, int> DataAPI::getWeather(const std::string &airportICAO) {
    const std::string link = "https://aviationweather.gov/api/data/metar?ids=" + airportICAO + "&format=json";
    const cpr::Response res = cpr::Get(cpr::Url{link});

    nlohmann::json metar = nlohmann::json::parse(res.text);

    int wdir = metar[0]["wdir"];
    int wspd = metar[0]["wspd"];

    return {wdir,wspd};
}*/

std::string DataAPI::getWeatherPath() {
    const std::string link = "https://api.rainviewer.com/public/weather-maps.json";
    const cpr::Response res = cpr::Get(cpr::Url{link});

    nlohmann::json api = nlohmann::json::parse(res.text);

    return api["radar"]["nowcast"].back()["path"];
}