//
// Created by bgd on 18.05.2024.
//

#include "../header/MockAPI.h"
#include "../header/ResourcesManager.h"

#include <fstream>

nlohmann::json MockAPI::getFlyingEntities() {
    const std::string region = ResourcesManager::Instance().getSelectedRegion();
    std::ifstream f("resources/mock_api/" + region + "/flyingEntities.json");

    nlohmann::json data = nlohmann::json::parse(f)["ac"];

    return data;
}

std::string MockAPI::getWeatherPath() {
    std::ifstream f("resources/mock_api/weahter-maps.json");

    nlohmann::json data = nlohmann::json::parse(f);

    return data["radar"]["nowcast"].back()["path"];
}

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
        while(window->pollEvent(tempEvent)) {}

    }

    fin.close();
    return res;
}