#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

class AssetsManager
{
public:
	AssetsManager();

	void LoadFont(const std::string key);
	sf::Font &GetFont(const std::string key);

	void LoadTexture(const std::string key, const std::string path);
	sf::Texture& GetTexture(const std::string key);

	void LoadSoundBuffer(const std::string key);
	sf::SoundBuffer& GetSoundBuffer(const std::string key);

private:

	std::map<std::string, sf::Font>m_Fonts;
	std::map<std::string, sf::Texture>m_Textures;
	std::map<std::string, sf::SoundBuffer>m_SoundBuffers;

};