#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class Region {
public:
    explicit Region(const std::string &region);

    std::vector<float>& getBounds();
    std::vector<std::string> getAirportsIcao() const;
    const std::unordered_map<std::string, std::pair<int, int>>& getAirports() const;
    std::vector<std::pair<float, float>>& getWeatherTiles();
    int getZoomLevel() const;
    int getRadius() const;
    const std::string& getName();

    void render(sf::RenderWindow* window) const;

private:
    void loadBoundary();
    void loadAirports();
    void loadWeatherTiles();

private:
    const std::string m_regionName;
    const std::filesystem::path path;

    sf::Texture m_regionTexture;
    sf::Sprite m_regionSprite;

    std::vector<std::pair<float, float>> m_weatherTiles;
    std::unordered_map<std::string, std::pair<int, int>> m_airports;
    std::vector<float> m_boundaries;
    int m_zoomLevel{};
    int m_radius{};
};
