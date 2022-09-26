#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class AssetsManager
{
private:
	AssetsManager();
	
	static AssetsManager* instance;

	std::map<std::string, sf::Font>m_Fonts;

public:
	static AssetsManager* Instance();

	void LoadFont(const std::string key, const std::string path);
	sf::Font& getFont(const std::string key);

};