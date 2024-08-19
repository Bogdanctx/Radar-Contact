#pragma once

#include "LiveAPI.hpp"

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

class MockAPI : public LiveAPI {
public:
    MockAPI() = default;
    explicit MockAPI(const Region& region) : LiveAPI(region) {}

    nlohmann::json downloadFlyingEntities() override;
    std::string getWeatherPath() override;
    std::vector<sf::Texture>& downloadWeatherTextures(sf::RenderWindow* window) override;
};
