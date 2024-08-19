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
// Purpose: This function returns the 'path' to the latest fetched weather data
//-----------------------------------------------------------
std::string MockAPI::getWeatherPath()
{
    std::ifstream f(std::filesystem::path("resources") / "mock_api" / "weather-maps.json");

    nlohmann::json data = nlohmann::json::parse(f);

    return data["radar"]["nowcast"].back()["path"];
}


//-----------------------------------------------------------
// Purpose: Used to download latest weather data based on the
// getWeatherPath() 'path'
//-----------------------------------------------------------
std::vector<sf::Texture>& MockAPI::downloadWeatherTextures(sf::RenderWindow* window)
{
    m_downloadedWeatherTextures.clear();

    std::ifstream fin(std::filesystem::path("resources") / "mock_api" / m_region.getName() / "links.txt");
    int numberOfLinks;
    fin >> numberOfLinks;

    for(int i = 0; i < numberOfLinks; i++) {
        std::string link;
        fin >> link;

        sf::Texture temp;
        const std::filesystem::path loadPath = std::filesystem::path("resources") / "mock_api" / m_region.getName() / link;

        temp.loadFromFile(loadPath.string());
        m_downloadedWeatherTextures.push_back(temp);

        sf::Event tempEvent{};
        while(window->pollEvent(tempEvent)) {} // loop through window events to prevent crashes
    }

    fin.close();

    return m_downloadedWeatherTextures;
}