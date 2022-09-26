#include "AssetsManager.h"

AssetsManager* AssetsManager::instance = NULL;

AssetsManager* AssetsManager::Instance()
{
	if (instance == NULL)
		instance = new AssetsManager();

	return instance;
}

void AssetsManager::LoadFont(const std::string key, const std::string path)
{
	sf::Font f;

	if (f.loadFromFile(path))
	{
		m_Fonts[key] = f;
	}

	return;
}

sf::Font& AssetsManager::getFont(const std::string key)
{
	return m_Fonts[key];
}

AssetsManager::AssetsManager()
{

}
