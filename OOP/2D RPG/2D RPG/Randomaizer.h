#pragma once
#include<random>
#include<time.h>

static std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));

inline int Genereta_int_random_number()
{ 
	std::uniform_int_distribution<int> intDistribution;
	return intDistribution(generator);
}

inline double Genereta_double_random_number()
{
	std::uniform_real_distribution<double> doubleDistribution;
	return doubleDistribution(generator);
}