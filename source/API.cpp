//
// Created by bgd on 18.05.2024.
//

#include "../header/API.h"
#include <cpr/cpr.h>
#include <SFML/Network.hpp>
#include "../header/ResourcesManager.h"

nlohmann::json API::getArrivals() {
    const std::string link = "https://data.vatsim.net/v3/vatsim-data.json";

    const cpr::Response res = cpr::Get(cpr::Url{link},
                                       cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                                       cpr::Parameters{{"anon", "true"}, {"key", "value"}});

    nlohmann::json data = nlohmann::json::parse(res.text);

    return data;
}

std::string API::getWeatherPath() {
    const std::string link = "https://api.rainviewer.com/public/weather-maps.json";
    const cpr::Response res = cpr::Get(cpr::Url{link});

    nlohmann::json data = nlohmann::json::parse(res.text);

    return data["radar"]["nowcast"].back()["path"];
}

std::vector<sf::Texture> API::getWeatherTextures(sf::RenderWindow *window) {
    sf::Http http{"http://tilecache.rainviewer.com"};
    sf::Http::Request request;
    sf::Http::Response api_response;

    request.setMethod(sf::Http::Request::Post);
    request.setHttpVersion(1, 1);
    request.setField("Content-Type", "application/x-www-form-urlencoded");

    const std::string path = API::getWeatherPath();
    std::vector<sf::Texture> res{};
    std::vector<std::pair<float, float>> tiles = ResourcesManager::Instance().getWeatherTiles();

    for(const std::pair<float, float> &tile: tiles) {
        sf::Texture temp_texture;

        const std::string link = path + "/256/6/" + std::to_string(tile.first) + '/' +
                                 std::to_string(tile.second) + "/2/1_0.png";
        request.setUri(link);

        api_response = http.sendRequest(request);

        temp_texture.loadFromMemory(api_response.getBody().data(), api_response.getBody().size());

        res.push_back(temp_texture);

        sf::Event tempEvent{};
        window->pollEvent(tempEvent);
    }

    return res;
}