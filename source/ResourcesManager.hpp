#ifndef OOP_RESOURCESMANAGER_H
#define OOP_RESOURCESMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Waypoint.hpp"

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <stdexcept>

class ErrorResourcesManager: public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class ErrorSound: public ErrorResourcesManager {
public:
    explicit ErrorSound(const std::string &message) : ErrorResourcesManager("Sound Error: " + message) {}
};

class ErrorTexture: public ErrorResourcesManager {
public:
    explicit ErrorTexture(const std::string &message) : ErrorResourcesManager("Texture Error: " + message) {}
};

class ErrorFont: public ErrorResourcesManager {
public:
    explicit ErrorFont(const std::string &message) : ErrorResourcesManager("Font Error: " + message) {}
};

class ErrorLatLongBox: public ErrorResourcesManager {
public:
    explicit ErrorLatLongBox(const std::string &message) : ErrorResourcesManager("LatLong Box error: " + message) {}
};

class ErrorWeatherTiles: public ErrorResourcesManager {
public:
    explicit ErrorWeatherTiles(const std::string &message) : ErrorResourcesManager("Weather Tiles Error: " + message) {}
};

class ErrorAirports: public ErrorResourcesManager {
public:
    explicit ErrorAirports(const std::string &message) : ErrorResourcesManager("Airports Error: " + message) {}
};

class ResourcesManager {
public:
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    static ResourcesManager& Instance();

    sf::Font &getFont(const std::string &key);
    sf::Texture& getTexture(const std::string &key);
    std::vector<float> getRegionBox();
    std::unordered_map<std::string, std::pair<int, int>> getRegionAirports() const;
    std::vector<std::pair<float, float>> getWeatherTiles() const;
    std::vector<std::string> getFacts() const;
    sf::SoundBuffer &getSound(const std::string &soundName);
    std::string getSelectedRegion() const;
    int getRegionZoomLevel() const;
    int getRegionRadius() const;

    void loadRegion(const std::string &region);
    void load();

    bool isMockingEnabled() const;
    void setMocking(bool status);

private:
    ResourcesManager();

    void loadTextures(const std::string &textureName);
    void loadFonts(const std::string &fontName);
    void loadWeatherTiles();
    void loadSounds(const std::string &sound_name);

    void loadLatLongBox();
    void loadAirports();

private:
    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::vector<float> m_regionBox;
    std::unordered_map<std::string, std::pair<int, int>> m_airports;
    std::vector<std::pair<float, float>> m_regionWeatherTiles;
    std::unordered_map<std::string, sf::SoundBuffer> m_sounds;
    std::vector<std::string> m_randomFacts;

    std::string m_selectedRegion;
    int m_regionZoomLevel;
    int m_regionRadius;
    bool m_usingMockApi;
};

#endif //OOP_RESOURCESMANAGER_H
