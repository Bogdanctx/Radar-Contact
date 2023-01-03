#include "AssetsManager.h"

AssetsManager::AssetsManager()
{

}

void AssetsManager::loadFont(const std::string key)
{
	sf::Font f;

	if (f.loadFromFile("../Resources/fonts/" + key))
	{
		m_Fonts[key] = f;
	}

	return;
}

sf::Font& AssetsManager::getFont(const std::string key)
{
	return m_Fonts.at(key);
}

void AssetsManager::loadTexture(const std::string key, const std::string path)
{
	sf::Texture t;

	if (t.loadFromFile(path + '/' + key))
	{
		m_Textures[key] = t;
	}

	return;
}

sf::Texture& AssetsManager::getTexture(const std::string key)
{
	return m_Textures.at(key);
}

void AssetsManager::loadSoundBuffer(const std::string key)
{
	sf::SoundBuffer s;

	if (s.loadFromFile("../Resources/sounds/" + key))
	{
		m_SoundBuffers[key] = s;
	}

	return;
}

sf::SoundBuffer& AssetsManager::getSoundBuffer(const std::string key)
{
	return m_SoundBuffers.at(key);
}

void AssetsManager::setResolution(unsigned short width, unsigned short height)
{
	resolution.width = width;
	resolution.height = height;
	resolution.scale = width / height;
}

AssetsManager::Resolution AssetsManager::getResolution()
{
	return resolution;
}
