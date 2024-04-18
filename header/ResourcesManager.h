//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_RESOURCESMANAGER_H
#define OOP_RESOURCESMANAGER_H

#include <SFML/Graphics.hpp>
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

    sf::Font &getFont(std::string key);
    sf::Texture& getTexture(std::string key);
    std::vector<float> getRegionBox(const std::string region);
    std::unordered_map<std::string, std::pair<int, int>> getRegionAirports(const std::string region);
    std::vector<std::pair<float, float>> getWeatherTiles(const std::string region);

    void load();

private:
    ResourcesManager() = default;

    void loadRegion(const std::string region);
    void loadTextures(const std::string textureName);
    void loadFonts(const std::string fontName);
    void loadWeatherTiles(const std::string region);

    std::unordered_map<std::string, sf::Font>m_fonts;
    std::unordered_map<std::string, sf::Texture>m_textures;
    std::unordered_map<std::string, std::vector<float>>m_regionBox;
    std::unordered_map<std::string, std::unordered_map<std::string, std::pair<int, int>>>m_airports;
    std::unordered_map<std::string, std::vector<std::pair<float, float>>> m_regionWeatherTiles;

};

#endif //OOP_RESOURCESMANAGER_H
