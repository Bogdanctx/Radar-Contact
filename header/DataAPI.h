//
// Created by bgd on 12.04.2024.
//

#ifndef OOP_DATAAPI_H
#define OOP_DATAAPI_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <unordered_set>
#include <utility>

#include "ResourcesManager.h"
#include "Math.h"

template<class T>
class DataAPI {
private:
    inline static std::unordered_set<std::string> m_fetchedEntities;
    inline static T api;

public:
    DataAPI() = default;
    ~DataAPI() = default;

    static nlohmann::json getArrivals() {
        nlohmann::json data = api.getArrivals();
        nlohmann::json arrivals;

        const int pilots_size = (int) data["pilots"].size();
        const std::vector<float> longLatBox{ResourcesManager::Instance().getRegionBox()};
        const std::unordered_map<std::string, std::pair<int, int>> regionAirports = ResourcesManager::Instance().getRegionAirports();

        for(const auto &airport: regionAirports)
        {
            const std::string airportIcao = airport.first;

            for(int i = 0; i < pilots_size; i++)
            {
                if(data["pilots"][i]["flight_plan"]["arrival"] == airportIcao)
                {
                    const std::string callsign = data["pilots"][i]["callsign"];

                    // daca avionul nu a mai fost adaugat in joc
                    if(m_fetchedEntities.find(callsign) == m_fetchedEntities.end())
                    {
                        int altitude = data["pilots"][i]["altitude"];
                        const float latitude = data["pilots"][i]["latitude"];
                        const float longitude = data["pilots"][i]["longitude"];
                        const sf::Vector2f mercatorProjection = Math::MercatorProjection(latitude, longitude, longLatBox);
                        const int distanceFromMiddle = Math::DistanceBetweenTwoPoints(sf::Vector2f(640, 360), mercatorProjection);

                        if(distanceFromMiddle <= 620 && altitude >= 2000 && altitude <= 40000) {
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


    static std::string getWeatherPath() {
        nlohmann::json result = api.getWeatherPath();

        return result["radar"]["nowcast"].back()["path"];
    }

    static std::vector<sf::Texture> getWeatherTextures(sf::RenderWindow *window) {
        return api.getWeatherTextures(window);
    }

};


#endif //OOP_DATAAPI_H
