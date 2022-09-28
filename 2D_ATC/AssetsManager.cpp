#include "AssetsManager.h"

AssetsManager::AssetsManager()
{

}

void AssetsManager::LoadFont(const std::string key)
{
	sf::Font f;
	
	if (f.loadFromFile("../Resources/fonts/" + key))
	{
		m_Fonts[key] = f;
	}

	return;
}

sf::Font &AssetsManager::GetFont(const std::string key)
{
	return m_Fonts.at(key);
}

void AssetsManager::LoadTexture(const std::string key, const std::string path)
{
	sf::Texture t;

	if (t.loadFromFile(path + '/' + key))
	{
		m_Textures[key] = t;
	}

	return;
}

sf::Texture& AssetsManager::GetTexture(const std::string key)
{
	return m_Textures.at(key);
}

void AssetsManager::LoadSoundBuffer(const std::string key)
{
	sf::SoundBuffer s;

	if (s.loadFromFile("../Resources/sounds/" + key))
	{
		m_SoundBuffers[key] = s;
	}

	return;
}

sf::SoundBuffer& AssetsManager::GetSoundBuffer(const std::string key)
{
	return m_SoundBuffers.at(key);
}


