#include "../header/LiveAPI.h"
#include "../header/ResourcesManager.h"
#include "../header/utils.h"

#include <cpr/cpr.h>
#include <SFML/Network.hpp>

nlohmann::json LiveAPI::getFlyingEntities() {
    const std::vector<float> bounds = ResourcesManager::Instance().getRegionBox();

    int latitudeAvg = static_cast<int>((bounds[0] + bounds[2]) / 2);
    int longitudeAvg = static_cast<int>((bounds[1] + bounds[3]) / 2);

    const std::string link = "https://api.airplanes.live/v2/point/" + std::to_string(latitudeAvg) + '/' \
                            + std::to_string(longitudeAvg) + "/" + std::to_string(ResourcesManager::Instance().getRegionRadius());
    
    const cpr::Response res = cpr::Get(cpr::Url{link},
                                       cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                                       cpr::Parameters{{"anon", "true"}, {"key", "value"}});

    nlohmann::json data = nlohmann::json::parse(res.text)["ac"];

    return data;
}

std::string LiveAPI::getWeatherPath() {
    const std::string link = "https://api.rainviewer.com/public/weather-maps.json";
    const cpr::Response res = cpr::Get(cpr::Url{link});

    nlohmann::json data = nlohmann::json::parse(res.text);

    return data["radar"]["nowcast"].back()["path"];
}

std::vector<sf::Texture> LiveAPI::getWeatherTextures(sf::RenderWindow* window) {
    sf::Http http{"http://tilecache.rainviewer.com"};
    sf::Http::Request request;
    sf::Http::Response api_response;

    request.setMethod(sf::Http::Request::Post);
    request.setHttpVersion(1, 1);
    request.setField("Content-Type", "application/x-www-form-urlencoded");

    const std::string path = LiveAPI::getWeatherPath();
    std::vector<sf::Texture> res;
    std::vector<std::pair<float, float>> tiles = ResourcesManager::Instance().getWeatherTiles();

    for(const std::pair<float, float> &tile: tiles) {
        sf::Texture temp_texture;

        std::string link = path + "/256/" + std::to_string(ResourcesManager::Instance().getRegionZoomLevel()) + "/" +
                            std::to_string(tile.first) + '/' + std::to_string(tile.second) + "/2/1_0.png";

        request.setUri(link);

        api_response = http.sendRequest(request);

        temp_texture.loadFromMemory(api_response.getBody().data(), api_response.getBody().size());

        res.push_back(temp_texture);

        sf::Event tempEvent{};
        while(window->pollEvent(tempEvent)) {} // poll through window events to prevent crashes
    }

    return res;
}
