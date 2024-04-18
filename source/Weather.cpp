//
// Created by bgd on 13.04.2024.
//

#include "../header/Weather.h"
#include "../header/Math.h"

// https://tilecache.rainviewer.com/v2/radar/1713089400/256/6/55.776575/-5.624999/2/1_0.png
// https://tilecache.rainviewer.com/v2/radar/1713041400/512/5/55.776575/-11.249998/1/1_0.png
Weather::Weather(const std::string region) :
        m_tiles{ResourcesManager::Instance().getWeatherTiles(region)},
        m_selectedRegion{region}
{

}

void Weather::render(sf::RenderWindow *window) {
    for(const sf::Sprite &sprite: m_sprites) {
        window->draw(sprite);
    }
}

void Weather::update() {
    if(m_updateWeather.getElapsedTime().asSeconds() >= 60*5) { // 5 minutes passed -> update weather
        fetchWeatherImages();
        m_updateWeather.restart();
    }
}

void Weather::fetchWeatherImages() {
    m_textures = std::vector<sf::Texture> {};
    m_sprites = std::vector<sf::Sprite> {};

    sf::Http http{"http://tilecache.rainviewer.com"};
    sf::Http::Request request;
    sf::Http::Response api_response;

    request.setMethod(sf::Http::Request::Post);
    request.setHttpVersion(1, 1);
    request.setField("Content-Type", "application/x-www-form-urlencoded");

    const std::string path = DataAPI::getWeatherPath();

    for(const std::pair<float, float> &tile: m_tiles) {
        sf::Texture temp_texture;
        /*const std::string link = path + "/256/7/" + std::to_string(tile.first) + '/' +
                                    std::to_string(tile.second) + "/2/1_0.png";*/
        const std::string link = path + "/256/6/" + std::to_string(tile.first) + '/' +
                                 std::to_string(tile.second) + "/2/1_0.png";
        request.setUri(link);

        api_response = http.sendRequest(request);

        temp_texture.loadFromMemory(api_response.getBody().data(), api_response.getBody().size());

        m_textures.push_back(temp_texture);
    }

    for(int i = 0; i < m_textures.size(); i++) {
        sf::Sprite temp_sprite;
        temp_sprite.setTexture(m_textures[i]);
        // temp_sprite.setScale(0.55f, 0.55f);
        sf::FloatRect bounds = temp_sprite.getLocalBounds();
        temp_sprite.setOrigin(bounds.width / 2, bounds.height / 2);

        sf::Vector2f projection = Math::MercatorProjection(m_tiles[i].first, m_tiles[i].second,
                                                           ResourcesManager::Instance().getRegionBox(m_selectedRegion));
        temp_sprite.setPosition(projection);
        m_sprites.push_back(temp_sprite);
    }
}