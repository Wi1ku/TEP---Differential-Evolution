#pragma once
#include "Optimizer.h"
class MeanSolver : Optimizer
{
public:
	MeanSolver(Problem& problem): Optimizer(&problem) { };
	double* solve(int stopCondition, int* errorCode) {
		double* solution = new double[problem->getSolutionSize()];
		double* minmax = problem->getMinmaxTable();
		int k = 0;
		for (int i = 0; i < problem->getSolutionSize(); i++)
		{
			solution[i] = (minmax[k] + minmax[k + 1]) / 2;
			k += 2;
		}
		delete[] minmax;
		return solution;
	};

};

