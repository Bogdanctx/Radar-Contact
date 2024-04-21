//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_RESOURCESMANAGER_H
#define OOP_RESOURCESMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <fstream>

class ResourcesManager {
public:
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    static ResourcesManager& Instance() {
        static ResourcesManager instance;
        return instance;
    }

    sf::Font &getFont(const std::string &key);
    sf::Texture& getTexture(const std::string &key);
    std::vector<float> getRegionBox(const std::string &region);
    std::unordered_map<std::string, std::pair<int, int>> getRegionAirports(const std::string &region);
    std::vector<std::pair<float, float>> getWeatherTiles(const std::string &region);
    std::vector<std::string> getFacts();
    sf::SoundBuffer &getSound(const std::string &soundName);
    std::string getSelectedRegion() const;


    void loadRegion(const std::string &region);
    void load();

private:
    ResourcesManager() : m_randomFacts{
            "Planes can fly with only one engine.",
            "Pilots and copilots typically eat different meals.",
            "The cabin is dimmed upon landing for emergency measures.",
            "The tanks of oxygen for passenger masks are only supposed to last 15 minutes.",
            "The tiny hole in the passenger windows helps regulate cabin pressure.",
            "Travelers lose out on over a third of their taste buds during flight.",
            "The first female pilot was a woman named Raymonde de Laroche.",
            "A Boeing 747 is made up of six million parts",
            "More than 80% of the population is afraid of flying",
            "Each engine on a Boeing 747 weighs almost 9,500 pounds",
    } {}

    void loadTextures(const std::string &textureName);
    void loadFonts(const std::string &fontName);
    void loadWeatherTiles(const std::string &region);
    void loadSounds(const std::string &sound_name);

    std::unordered_map<std::string, sf::Font>m_fonts{};
    std::unordered_map<std::string, sf::Texture>m_textures{};
    std::unordered_map<std::string, std::vector<float>>m_regionBox{};
    std::unordered_map<std::string, std::unordered_map<std::string, std::pair<int, int>>>m_airports{};
    std::unordered_map<std::string, std::vector<std::pair<float, float>>> m_regionWeatherTiles{};
    std::unordered_map<std::string, sf::SoundBuffer> m_sounds{};
    std::vector<std::string> m_randomFacts{};

    std::string m_selectedRegion{};
};

#endif //OOP_RESOURCESMANAGER_H
