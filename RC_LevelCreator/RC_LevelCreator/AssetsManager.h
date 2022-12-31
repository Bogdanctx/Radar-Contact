#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <utility>

class AssetsManager
{
public:
	AssetsManager();

	struct Resolution {
        unsigned short width, height;
	};

	void loadFont(const std::string key);
	sf::Font &getFont(const std::string key);

	void loadTexture(const std::string key, const std::string path);
	sf::Texture& getTexture(const std::string key);

	void loadSoundBuffer(const std::string key);
	sf::SoundBuffer& getSoundBuffer(const std::string key);

	void setResolution(unsigned short width, unsigned short height);
	Resolution getResolution();

private:
	std::unordered_map<std::string, sf::Font>m_Fonts;
	std::unordered_map<std::string, sf::Texture>m_Textures;
	std::unordered_map<std::string, sf::SoundBuffer>m_SoundBuffers;


	Resolution resolution;
};
