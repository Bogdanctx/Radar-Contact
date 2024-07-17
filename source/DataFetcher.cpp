#include "../header/DataFetcher.h"

nlohmann::json DataFetcher::getFlyingEntities(sf::RenderWindow* window) {
    const std::unordered_map<std::string, std::pair<int, int>> regionAirports = ResourcesManager::Instance().getRegionAirports();

    std::vector<std::string> airports;
    airports.reserve(regionAirports.size());

    std::transform(regionAirports.begin(), regionAirports.end(), std::back_inserter(airports),
                   [](const auto& elm) {
        return elm.first;
    });

    nlohmann::json data = m_api->getFlyingEntities();
    nlohmann::json flyingEntities{};

    std::shuffle(data.begin(), data.end(), std::mt19937(std::random_device()()));

    for(auto& item : data) {
        if(item["flight"].is_null() || item["t"].is_null() || item["alt_baro"].is_null() || item["alt_baro"].is_string() ||
           item["lon"].is_null() || item["lat"].is_null() || item["track"].is_null() || item["t"].is_null()) {
            continue;
        }

        int altitude = item["alt_baro"];
        altitude = altitude / 1000 * 1000;

        if(altitude < 2000) {
            continue;
        }

        int randomIndex = Utilities::randGen<int>(0, static_cast<int>(airports.size()) - 1);
        const std::string randomAirport = airports[randomIndex];

        if(item["squawk"].is_null()) {
            item["squawk"] = std::to_string(Utilities::randGen<int>(1000, 9999));
        }

        // remove the last 3 white spaces from the back of the callsign
        std::string callsign = item["flight"];
        callsign = callsign.substr(0, callsign.size() - 2);

        nlohmann::json flyingEntity = {
                {"callsign", callsign},
                {"altitude", altitude},
                {"squawk",   item["squawk"]},
                {"lon",      static_cast<float>(item["lon"])},
                {"lat",      static_cast<float>(item["lat"])},
                {"heading",  static_cast<int>(item["track"])},
                {"arrival",  randomAirport},
                {"type",     item["t"]}
        };

        flyingEntities.push_back(flyingEntity);

        sf::Event tempEvent;
        while(window->pollEvent(tempEvent)) {} // poll through window events to prevent crashes
    }

    return flyingEntities;
}

std::vector<sf::Texture> DataFetcher::getWeatherTextures(sf::RenderWindow* window) {
    return m_api->getWeatherTextures(window);
}

void DataFetcher::setAPI(std::shared_ptr<LiveAPI> api) {
    m_api = std::move(api);
}