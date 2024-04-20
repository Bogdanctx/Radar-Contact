//
// Created by bgd on 11.04.2024.
//

#include "../header/ResourcesManager.h"

void ResourcesManager::load()
{
    loadTextures("menu.png");
    loadTextures("loading_screen.png");

    loadSounds("plane_landing.wav");
    loadSounds("atc.wav");

    loadFonts("Poppins-Regular.ttf");
    loadFonts("Raleway-Regular.ttf");
}

void ResourcesManager::loadSounds(const std::string &sound_name) {
    const std::string path = "../resources/sounds/" + sound_name;
    sf::SoundBuffer sound;

    sound.loadFromFile(path);
    m_sounds[sound_name] = sound;
}

sf::SoundBuffer &ResourcesManager::getSound(const std::string &soundName) {
    return m_sounds[soundName];
}

std::vector<std::string> ResourcesManager::getFacts() {
    return m_randomFacts;
}

void ResourcesManager::loadFonts(const std::string &fontName)
{
    const std::string fontPath = "../resources/fonts/" + fontName;
    sf::Font font;

    font.loadFromFile(fontPath);
    m_fonts[fontName] = font;
}

sf::Font &ResourcesManager::getFont(const std::string &key)
{
    return m_fonts.at(key);
}

void ResourcesManager::loadTextures(const std::string &textureName)
{
    const std::string texturePath = "../resources/general_textures/" + textureName;
    sf::Texture texture;

    texture.loadFromFile(texturePath);

    m_textures[textureName] = texture;
}

sf::Texture &ResourcesManager::getTexture(const std::string &key)
{
    return m_textures.at(key);
}

std::string ResourcesManager::getSelectedRegion() const {
    return m_selectedRegion;
}

void ResourcesManager::loadRegion(const std::string &region_name) {
    m_selectedRegion = region_name;

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

    loadWeatherTiles(region_name);
}

std::vector<float> ResourcesManager::getRegionBox(const std::string &region) {
    return m_regionBox[region];
}

std::unordered_map<std::string, std::pair<int, int>> ResourcesManager::getRegionAirports(const std::string &region) {
    return m_airports[region];
}

void ResourcesManager::loadWeatherTiles(const std::string &region) {
    const std::string path = "../resources/regions/" + region + "/weather_tiles.txt";
    std::vector<std::pair<float, float>> tiles;
    std::ifstream fin(path);
    int n;
    fin>>n;
    for(int i = 0; i < n; i++) {
        float longitude, latitude;
        fin>>longitude>>latitude;
        tiles.emplace_back(latitude, longitude);
    }
    m_regionWeatherTiles[region] = tiles;
    fin.close();
}

std::vector<std::pair<float, float>> ResourcesManager::getWeatherTiles(const std::string &region) {
    return m_regionWeatherTiles[region];
}