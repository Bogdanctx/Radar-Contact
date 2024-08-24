#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <unordered_map>
#include <fstream>
#include <stdexcept>

class ResourcesManager {
public:
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    static ResourcesManager& Instance();

    sf::Font &getFont(const std::string &key);
    sf::Texture& getTexture(const std::string &key);
    const std::vector<std::string>& getFacts() const;
    sf::SoundBuffer &getSound(const std::string &soundName);

    void load();

    bool isMockingEnabled() const;
    void setMocking(bool status);

private:
    ResourcesManager();

    void loadTextures(const std::string &textureName);
    void loadFonts(const std::string &fontName);
    void loadSounds(const std::string &sound_name);

private:
    std::unordered_map<std::string, sf::Font> m_fonts{};
    std::unordered_map<std::string, sf::Texture> m_textures{};
    std::unordered_map<std::string, sf::SoundBuffer> m_sounds{};
    std::vector<std::string> m_randomFacts{};
};
