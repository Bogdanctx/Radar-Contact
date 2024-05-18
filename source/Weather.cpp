//
// Created by bgd on 13.04.2024.
//

#include "../header/Weather.h"
#include "../header/ResourcesManager.h"

#include "../header/DataAPI.h"
#include "../header/API.h"
#include "../header/MockAPI.h"

// https://tilecache.rainviewer.com/v2/radar/1713089400/256/6/55.776575/-5.624999/2/1_0.png
// https://tilecache.rainviewer.com/v2/radar/1713041400/512/5/55.776575/-11.249998/1/1_0.png
Weather::Weather() : m_tiles{ResourcesManager::Instance().getWeatherTiles()}
{}

void Weather::render(sf::RenderWindow *window) {
    for(const sf::Sprite &sprite: m_sprites) {
        window->draw(sprite);
    }
}

void Weather::fetchWeatherImages(sf::RenderWindow *window) {
    m_sprites = std::vector<sf::Sprite> {};

    m_textures = (ResourcesManager::Instance().isMockingEnabled() ? DataAPI<MockAPI>::getWeatherTextures(window) :
                                                                    DataAPI<API>::getWeatherTextures(window));

    for(int i = 0; i < (int) m_textures.size(); i++) {
        sf::Sprite temp_sprite;
        temp_sprite.setTexture(m_textures[i]);

        sf::FloatRect bounds = temp_sprite.getLocalBounds();
        temp_sprite.setOrigin(bounds.width / 2, bounds.height / 2);

        sf::Vector2f projection = Math::MercatorProjection(m_tiles[i].first, m_tiles[i].second,
                                                           ResourcesManager::Instance().getRegionBox());
        temp_sprite.setPosition(projection);
        m_sprites.push_back(temp_sprite);
    }
}