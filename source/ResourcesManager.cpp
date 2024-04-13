//
// Created by bgd on 11.04.2024.
//

#include "../header/ResourcesManager.h"

ResourcesManager::ResourcesManager() : m_game_resolution{0, 0}
{
    loadFonts("Raleway-Regular.ttf");
    loadFonts("Poppins-Regular.ttf");

    loadTextures("menu.png");

    loadRegion("UK");
}

void ResourcesManager::loadFonts(const std::string fontName)
{
    const std::string fontPath = "../resources/fonts/" + fontName;
    sf::Font font;

    font.loadFromFile(fontPath);
    m_fonts[fontName] = font;
}

sf::Font &ResourcesManager::getFont(const std::string key)
{
    return m_fonts.at(key);
}

void ResourcesManager::loadTextures(const std::string textureName)
{
    const std::string texturePath = "../resources/general_textures/" + textureName;
    sf::Texture texture;

    texture.loadFromFile(texturePath);

    m_textures[textureName] = texture;
}

sf::Texture &ResourcesManager::getTexture(std::string key)
{
    return m_textures.at(key);
}

void ResourcesManager::setResolution(std::pair<int, int> resolution) {
    m_game_resolution = resolution;
}

std::pair<int, int> ResourcesManager::getResolution() {
    return m_game_resolution;
}

void ResourcesManager::loadRegion(const std::string region_name) {
    const std::string region_position = "../resources/regions/" + region_name + "/long_lat.txt";
    const std::string region_airports = "../resources/regions/" + region_name + "/airports.txt";
    const std::string region_texture = "../resources/regions/" + region_name + "/" + region_name + ".png";

    sf::Texture texture;
    texture.loadFromFile(region_texture);
    m_textures[region_name] = texture;

    std::ifstream fin(region_position);
    std::vector<float> box;
    for(int i = 0; i < 4; i++) {
        float f;
        fin>>f;
        box.push_back(f);
    }
    m_regionBox[region_name] = box;
    fin.close();

    fin.open(region_airports);

    int numberOfAirports;
    fin>>numberOfAirports;
    for(int i = 0; i < numberOfAirports; i++)
    {
        std::string airportICAO;
        int x, y;
        fin>>x>>y>>airportICAO;

        m_airports[region_name][airportICAO] = {x, y};
    }

    fin.close();
}

std::vector<float> ResourcesManager::getRegionBox(const std::string region) {
    return m_regionBox[region];
}

std::unordered_map<std::string, std::pair<int, int>> ResourcesManager::getRegionAirports(const std::string region) {
    return m_airports[region];
}