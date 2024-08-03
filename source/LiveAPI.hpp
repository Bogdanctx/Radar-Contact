#ifndef OOP_API_H
#define OOP_API_H

#include <nlohmann/json.hpp>
#include <vector>
#include <SFML/Graphics.hpp>

class LiveAPI {
public:
    virtual ~LiveAPI() = default;

    virtual nlohmann::json getFlyingEntities();
    virtual std::string getWeatherPath();
    virtual std::vector<sf::Texture> getWeatherTextures(sf::RenderWindow* window);
};


#endif //OOP_API_H
