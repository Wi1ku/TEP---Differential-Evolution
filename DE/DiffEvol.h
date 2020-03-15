#pragma once
#include "MscnProblem.h"
#include "Optimizer.h"
#include "Timer.h"

class DiffEvol : public Optimizer
{
public:
	DiffEvol(Problem &problem, int populationSize);
	~DiffEvol();
	double* solve(int maxPopulationUpdates, int* errorCode);
	

private:
	Problem* problem;
	Table<double*> population;
	int populationSize;

	void initializePopulation();
	double* generateIndividual();
	double* getBestResult(int* errorCode);
	bool individualsAreDiffrent(double* i1, double* i2, double* i3, double* i4);
};

