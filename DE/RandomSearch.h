#pragma once
#include "Problem.h"
#include "Optimizer.h"
#include "Random.h"
#include "Solution.h"

class RandomSearch : public Optimizer
{
public:
	RandomSearch(Problem& problem);
	~RandomSearch();
	double* solve(int amountOfSearches, int* errorCode);
	

private:
	Problem* problem;
	double* getRandomSolution(int solutionSize, double minVal, double maxVal);
};

