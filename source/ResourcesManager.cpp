//
// Created by bgd on 11.04.2024.
//

#include "../header/ResourcesManager.h"

ResourcesManager::ResourcesManager() : m_game_resolution{0, 0}
{
    LoadFonts();
    LoadTextures();
}

void ResourcesManager::LoadFonts()
{
    sf::Font font;

    // font.loadFromFile();

    // m_fonts[nume_font] = font;
}

sf::Font &ResourcesManager::GetFont(const std::string key)
{
    return m_fonts.at(key);
}

void ResourcesManager::LoadTextures()
{
    sf::Texture texture;

    texture.loadFromFile("../resources/menu/menu.png");

    m_textures["menu.png"] = texture;
}

sf::Texture &ResourcesManager::GetTexture(const std::string key)
{
    return m_textures.at(key);
}

void ResourcesManager::SetResolution(std::pair<int, int> resolution) {
    m_game_resolution = resolution;
}

std::pair<int, int> ResourcesManager::GetResolution() {
    return m_game_resolution;
}