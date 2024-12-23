#include "Region.hpp"

#include <fstream>
#include <algorithm>

Region::Region(const std::string& region) : m_regionName(region),
                                            path(std::filesystem::path("resources") / "regions" / region),
                                            m_regionTexture(path / (region + ".png")),
                                            m_regionSprite(m_regionTexture)
{
    loadBoundary();
    loadAirports();
    loadWeatherTiles();
}

void Region::render(sf::RenderWindow* window) const
{
    window->draw(m_regionSprite);
}

const std::string& Region::getName()
{
    return m_regionName;
}


std::vector<float>& Region::getBounds()
{
    return m_boundaries;
}

std::vector<std::string> Region::getAirportsIcao() const
{
    std::vector<std::string> airports;

    std::transform(m_airports.begin(), m_airports.end(), std::back_inserter(airports),
                   [](const auto& elm) {
        return elm.first;
    });

    return airports;
}

const std::unordered_map<std::string, std::pair<int, int>>& Region::getAirports() const
{
    return m_airports;
}


std::vector<std::pair<float, float>>& Region::getWeatherTiles()
{
    return m_weatherTiles;
}

int Region::getZoomLevel() const
{
    return m_zoomLevel;
}

int Region::getRadius() const
{
    return m_radius;
}


void Region::loadAirports()
{
    std::ifstream fin(path / "airports.txt");
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


void Region::loadBoundary()
{
    std::ifstream fin(path / "long_lat.txt");

    for(int i = 0; i < 4; i++)
    {
        float coordinate;
        fin>>coordinate;
        m_boundaries.push_back(coordinate);
    }

    fin >> m_zoomLevel;
    fin >> m_radius;

    fin.close();
}

void Region::loadWeatherTiles()
{
    std::ifstream fin(path / "weather_tiles.txt");

    for(int i = 0; i < 15; i++) {
        float longitude, latitude;
        fin >> longitude >> latitude;
        m_weatherTiles.emplace_back(latitude, longitude);
    }

    fin.close();
}


