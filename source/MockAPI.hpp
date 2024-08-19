#pragma once

#include "LiveAPI.hpp"

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

class MockAPI : public LiveAPI {
public:
    explicit MockAPI(const Region& region) : LiveAPI(region) {}

    nlohmann::json downloadFlyingEntities() override;
    std::vector<sf::Texture>& downloadWeatherTextures(sf::RenderWindow* window) override;
};
