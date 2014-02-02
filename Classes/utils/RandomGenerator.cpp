#include "RandomGenerator.h"
#include <cstdlib>
#include <algorithm>
#include <numeric>


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
    double rnd;
    while(true){
        rnd = ((double) rand() / (RAND_MAX));
        if(rnd < 1.0){
            return rnd;
        }
    }
}

size_t RandomGenerator::getRandomID(std::vector<double> weights)
{
    if(weights.empty() || (weights.size() == 1)) return 0;
    
    double val;
    double sum;
    std::size_t result = 0;

    normalize(weights);
    
    while(true) {
        val = getRandom01();
        sum = 0;
        result = 0;
        for(std::vector<double>::const_iterator
            iter = weights.begin(),
            end = weights.end();
            iter != end; ++iter, ++result)
        {
            sum += *iter;
            if(sum > val) {
                return result;
            }
        }
    }
}


void RandomGenerator::normalize(std::vector<double> &probabilities)
{
    
    const double sum = std::accumulate(probabilities.begin(), probabilities.end(), static_cast<double>(0));
    for(std::vector<double>::iterator
        iter = probabilities.begin(),
        end = probabilities.end();
        iter != end; ++iter)
    {
        *iter /= sum;
    }
}