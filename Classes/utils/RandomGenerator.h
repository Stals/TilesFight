#pragma once

class RandomGenerator{
public:
	// не включая max!
	static int getRandom(int min, int max);
	static double getRandomDouble(double min, double max);
	static double getRandom01();

private:
	RandomGenerator();
};
