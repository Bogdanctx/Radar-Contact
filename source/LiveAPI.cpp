#include "LiveAPI.hpp"
#include "ResourcesManager.hpp"
#include <cpr/cpr.h>

//-----------------------------------------------------------
// Purpose: Download live data from API
//-----------------------------------------------------------
nlohmann::json LiveAPI::downloadFlyingEntities()
{
    const std::vector<float>& bounds = m_region.getBounds();
    int regionRadius = m_region.getRadius();

    int latitudeAvg = static_cast<int>((bounds[0] + bounds[2]) / 2);
    int longitudeAvg = static_cast<int>((bounds[1] + bounds[3]) / 2);

    const std::string link = "https://api.airplanes.live/v2/point/" + std::to_string(latitudeAvg) + '/' \
                            + std::to_string(longitudeAvg) + "/" + std::to_string(regionRadius);

    const cpr::Response res = cpr::Get(cpr::Url(link));

    nlohmann::json data = nlohmann::json::parse(res.text)["ac"];

    return data;
}


//-----------------------------------------------------------
// Purpose: This call returns the 'path' to the latest fetched weather data
//-----------------------------------------------------------
std::string LiveAPI::getWeatherPath() {
    const std::string link = "https://api.rainviewer.com/public/weather-maps.json";
    const cpr::Response res = cpr::Get(cpr::Url(link));

    nlohmann::json data = nlohmann::json::parse(res.text);

    return data["radar"]["nowcast"].back()["path"];
}

//-----------------------------------------------------------
// Purpose: Used to download latest weather data based on the
// getWeatherPath() 'path'
//-----------------------------------------------------------
void LiveAPI::downloadWeatherTextures()
{
    const std::vector<std::pair<float, float>>& tiles = m_region.getWeatherTiles();
    int regionZoomLevel = m_region.getZoomLevel();

    if(m_downloadedWeatherTextures.empty())
    {
        m_downloadedWeatherTextures.resize(15);
    }

    const std::string path = LiveAPI::getWeatherPath();

    for(int i = 0; i < 15; i++) {
        const std::pair<float, float> tile = tiles[i];

        std::string link = "https://tilecache.rainviewer.com" + path + "/256/" + std::to_string(regionZoomLevel) + "/" +
                            std::to_string(tile.first) + '/' + std::to_string(tile.second) + "/2/1_0.png";

        // reserve size because images are large string and request will be slow
        // https://docs.libcpr.org/advanced-usage.html#large-responses
        const cpr::Response res = cpr::Get(cpr::Url(link), cpr::ReserveSize(256 * 256));

        m_downloadedWeatherTextures[i].loadFromMemory(res.text.data(), res.text.size());
    }
}

const std::vector<sf::Texture>& LiveAPI::getWeatherTextures() const
{
    return m_downloadedWeatherTextures;
}

