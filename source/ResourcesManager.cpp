//
// Created by bgd on 11.04.2024.
//

#include "../header/ResourcesManager.h"
#include <mutex>

ResourcesManager::ResourcesManager() : m_randomFacts{
                                        "Planes can fly with only one engine.",
                                        "Pilots and copilots typically eat different meals.",
                                        "The cabin is dimmed upon landing for emergency measures.",
                                        "The tanks of oxygen for passenger masks are only supposed to last 15 minutes.",
                                        "The tiny hole in the passenger windows helps regulate cabin pressure.",
                                        "Travelers lose out on over a third of their taste buds during flight.",
                                        "The first female pilot was a woman named Raymonde de Laroche.",
                                        "A Boeing 747 is made up of six million parts",
                                        "More than 80% of the population is afraid of flying",
                                        "Each engine on a Boeing 747 weighs almost 9,500 pounds"},
                                        m_usingMockApi(false)
{

}

void ResourcesManager::load()
{
    loadTextures("menu.png");
    loadTextures("loading_screen.png");

    loadSounds("plane_landing.wav");
    loadSounds("atc.wav");

    loadFonts("Poppins-Regular.ttf");
    loadFonts("Raleway-Regular.ttf");
}

void ResourcesManager::setMocking(bool status) {
    m_usingMockApi = status;
}

bool ResourcesManager::isMockingEnabled() const {
    return m_usingMockApi;
}

void ResourcesManager::loadSounds(const std::string &sound_name) {
    const std::string path = "resources/sounds/" + sound_name;
    sf::SoundBuffer sound;

    if(!sound.loadFromFile(path)) {
        throw ErrorSound(sound_name + " missing or corrupted\n");
    }
    m_sounds[sound_name] = sound;
}

sf::SoundBuffer &ResourcesManager::getSound(const std::string &soundName) {
    return m_sounds[soundName];
}

std::vector<std::string> ResourcesManager::getFacts() const {
    return m_randomFacts;
}

void ResourcesManager::loadFonts(const std::string &fontName) {
    const std::string fontPath = "resources/fonts/" + fontName;
    sf::Font font;

    if(!font.loadFromFile(fontPath)) {
        throw ErrorFont(fontName + " missing or corrupted.\n");
    }

    m_fonts[fontName] = font;
}

sf::Font &ResourcesManager::getFont(const std::string &key) {
    return m_fonts.at(key);
}

void ResourcesManager::loadTextures(const std::string &textureName)
{
    const std::string texturePath = "resources/general_textures/" + textureName;
    sf::Texture texture;

    if(!texture.loadFromFile(texturePath)) {
        throw ErrorTexture(textureName + " missing or corrupted.\n");
    }

    m_textures[textureName] = texture;
}

sf::Texture &ResourcesManager::getTexture(const std::string &key) {
    return m_textures.at(key);
}

std::string ResourcesManager::getSelectedRegion() const {
    return m_selectedRegion;
}

void ResourcesManager::loadLatLongBox(const std::string &region_name) {
    static std::mutex mutex{};
    const std::string regionBox = "resources/regions/" + region_name + "/long_lat.txt";

    std::lock_guard<std::mutex> lockGuard(mutex);

    std::ifstream fin(regionBox);
    if(!fin.is_open()) {
        throw ErrorLatLongBox("Could not open long_lat.txt. It may be missing or corrupted\n");
    }

    for(int i = 0; i < 4; i++) {
        float coordinate;
        fin>>coordinate;
        m_regionBox.push_back(coordinate);
    }

    fin.close();
}

void ResourcesManager::loadAirports(const std::string &region_name) {
    const std::string regionAirports = "resources/regions/" + region_name + "/airports.txt";
    static std::mutex mutex{};

    std::lock_guard<std::mutex> lockGuard(mutex);

    std::ifstream fin(regionAirports);
    if(!fin.is_open()) {
        throw ErrorAirports("Could not open airports.txt. It may be missing or corrupted.\n");
    }

    int numberOfAirports;
    fin >> numberOfAirports;
    for(int i = 0; i < numberOfAirports; i++)
    {
        std::string airportICAO;
        int x, y;
        fin >> x >> y >> airportICAO;

        m_airports[airportICAO] = {x, y};
    }

    fin.close();
}

void ResourcesManager::loadRegion(const std::string &region_name) {
    m_selectedRegion = region_name;

    loadLatLongBox(region_name);
    loadAirports(region_name);
    loadWeatherTiles(region_name);

    // load region background
    const std::string region_texture = "resources/regions/" + region_name + "/" + region_name + ".png";
    if(!m_textures[region_name].loadFromFile(region_texture)) {
        throw ErrorTexture(region_name + " missing or corrupted.\n");
    }
    //////
}

std::vector<float> ResourcesManager::getRegionBox() {
    return m_regionBox;
}

std::unordered_map<std::string, std::pair<int, int>> ResourcesManager::getRegionAirports() const {
    return m_airports;
}

void ResourcesManager::loadWeatherTiles(const std::string &region) {
    const std::string path = "resources/regions/" + region + "/weather_tiles.txt";
    static std::mutex mutex{};

    std::lock_guard<std::mutex> lockGuard(mutex);

    std::ifstream fin(path);
    if(!fin.is_open()) {
        throw ErrorWeatherTiles("Could not open weather_tiles.txt. It may be missing or corrupted.\n");
    }

    int numberOfTiles;
    fin >> numberOfTiles;

    for(int i = 0; i < numberOfTiles; i++) {
        float longitude, latitude;
        fin >> longitude >> latitude;
        m_regionWeatherTiles.emplace_back(latitude, longitude);
    }

    fin.close();
}

std::vector<std::pair<float, float>> ResourcesManager::getWeatherTiles() const {
    return m_regionWeatherTiles;
}