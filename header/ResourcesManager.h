//
// Created by bgd on 11.04.2024.
//

#ifndef OOP_RESOURCESMANAGER_H
#define OOP_RESOURCESMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourcesManager {
public:
    ResourcesManager();
    ~ResourcesManager() = default;

    void LoadFonts();
    sf::Font &GetFont(std::string key);

    void LoadTextures();
    sf::Texture& GetTexture(std::string key);

    void SetResolution(std::pair<int, int> resolution);

    std::pair<int, int> GetResolution();

private:
    std::unordered_map<std::string, sf::Font>m_fonts;
    std::unordered_map<std::string, sf::Texture>m_textures;

    std::pair<int, int> m_game_resolution;
};


#endif //OOP_RESOURCESMANAGER_H
