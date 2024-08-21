#include "MockAPI.hpp"

#include <fstream>


//-----------------------------------------------------------
// Purpose: Download air traffic from local data
//-----------------------------------------------------------
nlohmann::json MockAPI::downloadFlyingEntities()
{
    std::ifstream f(std::filesystem::path("resources") / "mock_api" / m_region.getName() / "airtraffic.json");

    nlohmann::json data = nlohmann::json::parse(f);

    return data["ac"];
}

//-----------------------------------------------------------
// Purpose: Used to download latest weather data based on the
// getWeatherPath() 'path'
//-----------------------------------------------------------
void MockAPI::downloadWeatherTextures()
{
    m_downloadedWeatherTextures.clear();

    for(int i = 0; i < 15; i++)
    {
        sf::Texture temp;
        const std::filesystem::path loadPath = std::filesystem::path("resources") / "mock_api" / m_region.getName() / (std::to_string(i) + ".png");

        temp.loadFromFile(loadPath.string());
        m_downloadedWeatherTextures.push_back(temp);
    }
}