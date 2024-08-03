#include "MockAPI.hpp"
#include "ResourcesManager.hpp"

#include <fstream>


//-----------------------------------------------------------
// Purpose: Download air traffic from local data
//-----------------------------------------------------------
nlohmann::json MockAPI::getFlyingEntities() {
    const std::string region = ResourcesManager::Instance().getSelectedRegion();
    std::ifstream f("resources/mock_api/" + region + "/airtraffic.json");

    nlohmann::json data = nlohmann::json::parse(f);

    return data["ac"];
}


//-----------------------------------------------------------
// Purpose: This call returns the 'path' to the latest fetched weather data
//-----------------------------------------------------------
std::string MockAPI::getWeatherPath() {
    std::ifstream f("resources/mock_api/weahter-maps.json");

    nlohmann::json data = nlohmann::json::parse(f);

    return data["radar"]["nowcast"].back()["path"];
}


//-----------------------------------------------------------
// Purpose: Used to download latest weather data based on the
// getWeatherPath() 'path'
//-----------------------------------------------------------
std::vector<sf::Texture> MockAPI::getWeatherTextures(sf::RenderWindow* window) {
    const std::string region = ResourcesManager::Instance().getSelectedRegion();
    std::vector<sf::Texture> res{};

    std::ifstream fin("./resources/mock_api/" + region + "/links.txt");
    int numberOfLinks;
    fin >> numberOfLinks;

    for(int i = 0; i < numberOfLinks; i++) {
        std::string link;
        fin >> link;

        sf::Texture temp;
        temp.loadFromFile("./resources/mock_api/" + region + '/' + link);
        res.push_back(temp);

        sf::Event tempEvent{};
        while(window->pollEvent(tempEvent)) {} // loop through window events to prevent crashes

    }

    fin.close();
    return res;
}