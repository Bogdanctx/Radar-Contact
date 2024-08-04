#include "DataFetcher.hpp"
#include "ResourcesManager.hpp"
#include "utils.hpp"

//-----------------------------------------------------------
// Purpose: Build data based on APIs response
//-----------------------------------------------------------
nlohmann::json DataFetcher::getFlyingEntities(sf::RenderWindow* window, int& fetchedCounter) {
    // All data downloaded from API must be consumed before requesting new data from API
    // This is to prevent spamming the API
    if(m_flyingEntities.is_null() || fetchedCounter >= static_cast<int>(m_flyingEntities.size())) {
        fetchedData = m_api->getFlyingEntities();
        m_flyingEntities.clear();
        fetchedCounter = 0;
    }
    else {
        return m_flyingEntities;
    }

    const std::unordered_map<std::string, std::pair<int, int>> regionAirports = ResourcesManager::Instance().getRegionAirports();

    std::vector<std::string> airports;
    airports.reserve(regionAirports.size());

    std::transform(regionAirports.begin(), regionAirports.end(), std::back_inserter(airports),
                   [](const auto& elm) {
        return elm.first;
    });

    for(auto& item : fetchedData) {
        if(item["flight"].is_null() || item["t"].is_null() || item["alt_baro"].is_null() || item["alt_baro"].is_string() ||
           item["lon"].is_null() || item["lat"].is_null() || item["track"].is_null() || item["t"].is_null() || item["gs"].is_null()) {
            continue;
        }

        int airspeed = item["gs"];
        if(airspeed < 120) {
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
        callsign.resize(callsign.size() - 2);

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

        m_flyingEntities.push_back(flyingEntity);

        sf::Event tempEvent{};
        while(window->pollEvent(tempEvent)) {} // poll through window events to prevent crashes
    }

    return m_flyingEntities;
}

void DataFetcher::reset() {
    m_flyingEntities.clear();
    fetchedData.clear();
}

size_t DataFetcher::getFlyingEntitiesLength() {
    return m_flyingEntities.size();
}

//-----------------------------------------------------------
// Purpose: Get textures fetched from APIs
//-----------------------------------------------------------
std::vector<sf::Texture> DataFetcher::getWeatherTextures(sf::RenderWindow* window) {
    return m_api->getWeatherTextures(window);
}

//-----------------------------------------------------------
// Purpose: Set m_api to be either LiveAPI or MockAPI
//-----------------------------------------------------------
void DataFetcher::setAPI(std::shared_ptr<LiveAPI> api) {
    m_api = std::move(api);
}