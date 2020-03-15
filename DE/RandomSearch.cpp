#include "RandomSearch.h"
#include "Timer.h"

RandomSearch::RandomSearch(Problem& problem) {
	this->problem = &problem;
}

RandomSearch::~RandomSearch() {
}

double* RandomSearch::solve(int amountOfSeconds, int* errorCode) {
	double bestQuality = -DBL_MAX;
	double* solution = new double[problem->getSolutionSize()];
	double* currentSolution;
	*errorCode = 0;
	Timer t;
	t.startMeasure();
	while (t.stopMeasure() < amountOfSeconds)
	{
		currentSolution = getRandomSolution(problem->getSolutionSize(),MIN_GENERATED_VALUE, MAX_GENERATED_VALUE);

		double currentQuality = problem->getQuality(currentSolution, errorCode);

		if (currentQuality > bestQuality) {
				bestQuality = currentQuality;
				delete[] solution;
				solution = currentSolution;
			}
			else {
				delete currentSolution;
			}

			if (*errorCode != 0) {
				(*errorCode)++;
			}
	}

	return solution;
}

double* RandomSearch::getRandomSolution(int solutionSize, double minVal, double maxVal){
	Random r;
	double* solution = new double[solutionSize];
	for (int i = 0; i < solutionSize; i++)
	{
		solution[i] = r.getNextDouble(minVal, maxVal);
	}
	return solution;
}



