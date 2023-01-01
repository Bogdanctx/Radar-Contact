#include <iostream>
#include "Engine.h"

int main()
{
	std::string icao;
	std::string airportName;

	std::cout << "Enter ICAO of the airport you want to edit: ";
	std::cin >> icao;
	std::cout << "Enter airport name: ";
	std::cin >> airportName;

	Engine engine;

	engine.load(icao, airportName);
	engine.run();

	return 0;
}