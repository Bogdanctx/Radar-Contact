//
// Created by bgd on 18.05.2024.
//

#ifndef OOP_API_H
#define OOP_API_H

#include <nlohmann/json.hpp>
#include <vector>
#include <SFML/Graphics.hpp>

class API {
public:
    virtual nlohmann::json getArrivals();
    virtual std::string getWeatherPath();
    virtual std::vector<sf::Texture> getWeatherTextures(sf::RenderWindow *window);
};


#endif //OOP_API_H
