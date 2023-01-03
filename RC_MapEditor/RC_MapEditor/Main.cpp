#include <iostream>
#include <SFML/Graphics.hpp>

#include "Engine.h"

int main()
{
	std::string icao;
	std::string airportName;

	std::cout << "Enter airport icao: "; std::cin >> icao;
	std::cout << "Enter airport name: "; std::cin >> airportName;

	Engine engine;

	engine.load(icao, airportName);
	engine.run();

	return 0;
}