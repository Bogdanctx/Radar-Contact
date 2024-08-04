#pragma once

////////////////////////////////////////////////////////////////////
//                                                                //
//      THIS CLASS BUILDS UP DATA REQUIRED BY GAME FROM APIS      //
//                                                                //
////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "LiveAPI.hpp"

class DataFetcher {
public:
    static nlohmann::json getFlyingEntities(sf::RenderWindow* window, int& fetchedCounter);
    static std::vector<sf::Texture> getWeatherTextures(sf::RenderWindow* window);
    static void setAPI(std::shared_ptr<LiveAPI> api);

    static size_t getFlyingEntitiesLength();
    static void reset();

private:
    inline static std::shared_ptr<LiveAPI> m_api;
    inline static nlohmann::json fetchedData;
    inline static nlohmann::json m_flyingEntities;
};
