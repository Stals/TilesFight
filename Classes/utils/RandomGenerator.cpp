#include "RandomGenerator.h"
#include <cstdlib>

int RandomGenerator::getRandom(int min, int max)
{
	return rand() % (max-min) + min;
}

double RandomGenerator::getRandomDouble(double min, double max)
{
    return min + getRandom01()  * (max - min);
}

double RandomGenerator::getRandom01()
{
	return ((double) rand() / (RAND_MAX));
}