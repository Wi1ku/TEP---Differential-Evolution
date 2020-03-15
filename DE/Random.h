#pragma once
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>

class Random
{
public:
	Random();
	Random(unsigned int Seed);
	int getNextInt(int a, int b);
	double getNextDouble(double a, double b);

private:
	unsigned int instanceSeed;
	std::default_random_engine generator;

};

