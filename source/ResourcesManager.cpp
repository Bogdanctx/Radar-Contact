#include "ResourcesManager.hpp"
#include "Math.hpp"

#include <filesystem>

ResourcesManager::ResourcesManager() : m_randomFacts{
                                        "Planes can fly with only one engine.",
                                        "Pilots and copilots typically eat different meals.",
                                        "The cabin is dimmed upon landing for emergency measures.",
                                        "The tanks of oxygen for passenger masks are only supposed to last 15 minutes.",
                                        "The tiny hole in the passenger windows helps regulate cabin pressure.",
                                        "Travelers lose out on over a third of their taste buds during flight.",
                                        "The first female pilot was a woman named Raymonde de Laroche.",
                                        "Black Boxes aren't black.",
                                        "More than 80% of the population is afraid of flying.",
                                        "Each engine on a Boeing 747 weighs almost 9,500 pounds.",
                                        "The largest airplane ever built is called the Antonov An-225 Mriya.",
                                        "The largest airplane ever built, Antonov An-225 Mriya, was destroyed in 2022.",
                                        "Concorde was a passenger airplane that flew faster than the speed of sound."
                                        } {}

void ResourcesManager::load() {
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

void ResourcesManager::loadSounds(const std::string& sound_name) {
    const std::filesystem::path path = std::filesystem::path("resources") / "sounds" / sound_name;
    sf::SoundBuffer sound;

    if(!sound.loadFromFile(path.string())) {
        throw ErrorSound(sound_name + " missing or corrupted\n");
    }
    m_sounds[sound_name] = sound;
}

sf::SoundBuffer& ResourcesManager::getSound(const std::string& soundName) {
    return m_sounds[soundName];
}

const std::vector<std::string>& ResourcesManager::getFacts() const {
    return m_randomFacts;
}

void ResourcesManager::loadFonts(const std::string &fontName) {
    const std::filesystem::path path = std::filesystem::path("resources") / "fonts" / fontName;
    sf::Font font;

    if(!font.loadFromFile(path.string())) {
        throw ErrorFont(fontName + " missing or corrupted.\n");
    }

    m_fonts[fontName] = font;
}

sf::Font &ResourcesManager::getFont(const std::string &key) {
    return m_fonts.at(key);
}

void ResourcesManager::loadTextures(const std::string &textureName) {
    const std::filesystem::path path = std::filesystem::path("resources") / "general_textures" / textureName;
    sf::Texture texture;

    if(!texture.loadFromFile(path.string())) {
        throw ErrorTexture(textureName + " missing or corrupted.\n");
    }

    m_textures[textureName] = texture;
}

sf::Texture &ResourcesManager::getTexture(const std::string &key) {
    return m_textures.at(key);
}

const std::string& ResourcesManager::getSelectedRegion() const {
    return m_selectedRegion;
}

//-----------------------------------------------------------
// Purpose: Load the regions latitude and longitude bounds,
// zoom level and the radius used to fetch airplanes based on a point
//-----------------------------------------------------------
void ResourcesManager::loadLatLongBox() {
    m_regionBox.clear();

    const std::filesystem::path path = std::filesystem::path("resources") / "regions" / m_selectedRegion / "long_lat.txt";

    std::ifstream fin(path);
    if(!fin.is_open()) {
        throw ErrorLatLongBox("Could not open long_lat.txt. It may be missing or corrupted\n");
    }

    for(int i = 0; i < 4; i++) {
        float coordinate;
        fin>>coordinate;
        m_regionBox.push_back(coordinate);
    }

    fin >> m_regionZoomLevel;

    fin >> m_regionRadius;

    fin.close();
}

int ResourcesManager::getRegionRadius() const {
    return m_regionRadius;
}

int ResourcesManager::getRegionZoomLevel() const {
    return m_regionZoomLevel;
}

void ResourcesManager::loadAirports() {
    m_airports.clear();

    const std::filesystem::path path = std::filesystem::path("resources") / "regions" / m_selectedRegion / "airports.txt";

    std::ifstream fin(path);
    if(!fin.is_open()) {
        throw ErrorAirports("Could not open airports.txt. It may be missing or corrupted.\n");
    }

    int numberOfAirports;
    fin >> numberOfAirports;
    for(int i = 0; i < numberOfAirports; i++) {
        std::string airportICAO;
        int x, y;
        fin >> x >> y >> airportICAO;

        m_airports[airportICAO] = {x, y};
    }

    fin.close();
}

void ResourcesManager::loadRegion(const std::string &region_name) {
    m_selectedRegion = region_name;

    loadLatLongBox();
    loadAirports();
    loadWeatherTiles();

    // load region background
    const std::filesystem::path path = std::filesystem::path("resources") / "regions" / region_name / (region_name + ".png");
    if(!m_textures[region_name].loadFromFile(path.string())) {
        throw ErrorTexture(region_name + " missing or corrupted.\n");
    }
    //////
}

const std::vector<float>& ResourcesManager::getRegionBox() {
    return m_regionBox;
}

const std::unordered_map<std::string, std::pair<int, int>>& ResourcesManager::getRegionAirports() const {
    return m_airports;
}

//-----------------------------------------------------------
// Purpose: Load latitude and longitude of weather tiles coordinates
//-----------------------------------------------------------
void ResourcesManager::loadWeatherTiles() {
    m_regionWeatherTiles.clear();

    const std::filesystem::path path = std::filesystem::path("resources") / "regions" / m_selectedRegion / "weather_tiles.txt";

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

const std::vector<std::pair<float, float>>& ResourcesManager::getWeatherTiles() const {
    return m_regionWeatherTiles;
}

ResourcesManager& ResourcesManager::Instance() {
    static ResourcesManager instance;
    return instance;
}