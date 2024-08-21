#include "Weather.hpp"
#include "ResourcesManager.hpp"
#include "Math.hpp"

// https://tilecache.rainviewer.com/v2/radar/1713089400/256/6/55.776575/-5.624999/2/1_0.png
// https://tilecache.rainviewer.com/v2/radar/1713041400/512/5/55.776575/-11.249998/1/1_0.png
void Weather::render(sf::RenderWindow *window) {
    for(const sf::Sprite& sprite: m_sprites) {
        window->draw(sprite);
    }
}

//-----------------------------------------------------------
// Purpose: Return the color of a pixel inside a specific sprite
//-----------------------------------------------------------
int Weather::getPixelColor(const sf::Sprite& sprite, sf::Vector2i position)
{
    sf::Vector2i spritePosition = static_cast<sf::Vector2i>(sf::Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top));

    sf::Vector2u pixelPosition(position.x - spritePosition.x, position.y - spritePosition.y);

    if(pixelPosition.x == 256) {
        pixelPosition.x -= 1;
    }
    if(pixelPosition.y == 256) {
        pixelPosition.y -= 1;
    }

    sf::Color pixelColor = sprite.getTexture()->copyToImage().getPixel(pixelPosition.x, pixelPosition.y);

    struct Color {
        int r, g, b;
    };

    const std::vector<Color> colors = {
            {255, 191, 0},   // yellow
            {0, 118, 170},   // blue
            {189, 0, 0},     // red
            {255, 157, 255}, // pink
            {0, 0, 0},       // nothing
            {206, 192, 138}  // not-dangerous yellow
    };

    int minDistance = std::numeric_limits<int>::max();
    int colorIndex = -1;

    for (int i = 0; i < static_cast<int>(colors.size()); i++) {
        int dr = pixelColor.r - colors[i].r;
        int dg = pixelColor.g - colors[i].g;
        int db = pixelColor.b - colors[i].b;

        int distance = dr * dr + dg * dg + db * db;

        if (distance < minDistance) {
            minDistance = distance;
            colorIndex = i;
        }
    }

    return colorIndex;
}

//-----------------------------------------------------------
// Purpose: Update sprite images
//-----------------------------------------------------------
void Weather::updateImages(const std::vector<sf::Texture>& textures, const std::vector<float>& regionBoundaries,
                                const std::vector<std::pair<float, float>>& tiles)
{
    if(m_sprites.empty())
    {
        m_sprites.resize(15);
    }

    for(int i = 0; i < 15; i++)
    {
        m_sprites[i].setTexture(textures[i]);

        sf::Color color = m_sprites[i].getColor();
        m_sprites[i].setColor(sf::Color(color.r, color.g, color.b, 140));

        sf::FloatRect bounds = m_sprites[i].getLocalBounds();
        m_sprites[i].setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

        sf::Vector2f projection = Math::MercatorProjection(tiles[i].first, tiles[i].second, regionBoundaries);
        m_sprites[i].setPosition(projection);
    }
}

std::vector<sf::Sprite>& Weather::getSprites() {
    return m_sprites;
}