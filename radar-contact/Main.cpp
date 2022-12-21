#include <random>
#include <ctime>

#include "Engine.h"

int main()
{
	srand(time(0));

	Engine engine;

	engine.run();

	return 0;
}