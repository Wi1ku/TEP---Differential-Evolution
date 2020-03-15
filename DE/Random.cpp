#include "Random.h"

Random::Random() {
	this->instanceSeed = std::chrono::system_clock::now().time_since_epoch().count();
	this->generator = std::default_random_engine(instanceSeed);
}

Random::Random(unsigned int seed) {
	this->instanceSeed = seed;
	this->generator = std::default_random_engine(instanceSeed);
}

int Random::getNextInt(int a, int b) {
	std::uniform_int_distribution<int> distribution(a, b);
	return distribution(generator);
}

double Random::getNextDouble(double a, double b) {
	std::uniform_real_distribution<double> distribution(a, b);
	return distribution(generator);
}
