#ifndef RADAR_CONTACT_MOCKAPI_H
#define RADAR_CONTACT_MOCKAPI_H

#include "LiveAPI.hpp"

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

class MockAPI : public LiveAPI {
public:
    nlohmann::json getFlyingEntities() override;
    std::string getWeatherPath() override;
    std::vector<sf::Texture> getWeatherTextures(sf::RenderWindow* window) override;
};


#endif //RADAR_CONTACT_MOCKAPI_H
