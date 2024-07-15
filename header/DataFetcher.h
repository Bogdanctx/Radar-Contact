//
// Created by bgd on 12.04.2024.
//

#ifndef OOP_DATAAPI_H
#define OOP_DATAAPI_H

/////////////////////////////////////////////////
//                                             //
//      THIS CLASS FETCHES DATA FROM APIS      //
//                                             //
/////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <random>
#include <unordered_set>
#include <utility>

#include "ResourcesManager.h"
#include "Math.h"
#include "utils.h"

#include "LiveAPI.h"

class DataFetcher {
private:
    inline static std::shared_ptr<LiveAPI> m_api{};
public:
    static nlohmann::json getFlyingEntities(sf::RenderWindow* window);
    static std::vector<sf::Texture> getWeatherTextures(sf::RenderWindow* window);
    static void setAPI(std::shared_ptr<LiveAPI> api);
};


#endif //OOP_DATAAPI_H
