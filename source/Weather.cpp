//
// Created by bgd on 13.04.2024.
//

#include "../header/Weather.h"
#include "../header/Math.h"

// https://tilecache.rainviewer.com/v2/radar/1713089400/256/6/55.776575/-5.624999/2/1_0.png
// https://tilecache.rainviewer.com/v2/radar/1713041400/512/5/55.776575/-11.249998/1/1_0.png
Weather::Weather(ResourcesManager &resourcesManager, const std::string region) :
                m_tiles{resourcesManager.getWeatherTiles(region)},
                m_resourcesManager(resourcesManager),
                m_selectedRegion{region}
{
    fetchWeatherImages();
}

void Weather::render(sf::RenderWindow *window) {
    for(const sf::Sprite &sprite: m_sprites) {
        window->draw(sprite);
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

    for(const std::pair<float, float> &tile: m_tiles) {
        sf::Texture temp_texture;
        const std::string link = "/v2/radar/nowcast_2f329a280afd/256/6/" + std::to_string(tile.first) + '/' +
                                    std::to_string(tile.second) + "/2/1_0.png";

        request.setUri(link);

        api_response = http.sendRequest(request);

        temp_texture.loadFromMemory(api_response.getBody().data(), api_response.getBody().size());

        m_textures.push_back(temp_texture);
    }

    for(int i = 0; i < m_textures.size(); i++) {
        sf::Sprite temp_sprite;
        temp_sprite.setOrigin(128, 128);
        temp_sprite.setTexture(m_textures[i]);

        sf::Vector2f projection = Math::MercatorProjection(m_tiles[i].first, m_tiles[i].second,
                                                           m_resourcesManager.getRegionBox(m_selectedRegion),
                                                           m_resourcesManager.getResolution());
        temp_sprite.setPosition(projection);
        m_sprites.push_back(temp_sprite);
    }
}