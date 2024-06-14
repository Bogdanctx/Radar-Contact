//
// Created by bgd on 18.05.2024.
//

#ifndef RADAR_CONTACT_MOCKAPI_H
#define RADAR_CONTACT_MOCKAPI_H

#include "API.h"

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

class MockAPI : public LiveAPI {
public:
    nlohmann::json getArrivals() override;
    std::string getWeatherPath() override;
    std::vector<sf::Texture> getWeatherTextures(sf::RenderWindow *window) override;
};


#endif //RADAR_CONTACT_MOCKAPI_H
