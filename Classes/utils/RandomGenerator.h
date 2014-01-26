#pragma once
#include <vector>

class RandomGenerator{
public:
	// не включая max!
	static int getRandom(int min, int max);
	static double getRandomDouble(double min, double max);
	static double getRandom01();
    
    static void normalize(std::vector<double> &weights);
    static size_t getRandomID(std::vector<double> weights);

private:
	RandomGenerator();
};
