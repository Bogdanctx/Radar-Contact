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

void ResourcesManager::loadSounds(const std::string& sound_name) {
    const std::filesystem::path path = std::filesystem::path("resources") / "sounds" / sound_name;
    sf::SoundBuffer sound;

    if(!sound.loadFromFile(path.string())) {
        throw std::runtime_error(sound_name + " missing or corrupted\n");
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

    if(!font.openFromFile(path.string())) {
        throw std::runtime_error(fontName + " missing or corrupted.\n");
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
        throw std::runtime_error(textureName + " missing or corrupted.\n");
    }

    m_textures[textureName] = texture;
}

sf::Texture &ResourcesManager::getTexture(const std::string &key) {
    return m_textures.at(key);
}

ResourcesManager& ResourcesManager::Instance() {
    static ResourcesManager instance;
    return instance;
}