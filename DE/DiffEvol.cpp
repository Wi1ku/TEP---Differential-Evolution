#include "DiffEvol.h"
#include "Constants.h"

double clip(double x, double min, double max) {
	if (x < min) return min;
	else if (x > max) return max;
	else return x;
}

DiffEvol::DiffEvol(Problem& problem, int populationSize) {
	this->problem = &problem;
	this->populationSize = populationSize;
	this->population = Table<double*>(populationSize);
}

DiffEvol::~DiffEvol() {
	for (int i = 0; i < this->populationSize; i++)
	{
		delete[] this->population.get(i);
	}
}

void DiffEvol::initializePopulation() {
	for (int i = 0; i < this->populationSize; i++) {
		this->population.setValueAt(i, generateIndividual());
	}
}


bool DiffEvol::individualsAreDiffrent(double* i1, double* i2, double* i3, double* i4) {
	return !(i1 == i2 || i1 == i3 || i1 == i4 || i2 == i3 || i2 == i4 || i3 == i4);
}

double* DiffEvol::generateIndividual() {

	Random r;
	double* solution = new double[problem->getSolutionSize()];
	for (int i = 0; i < problem->getSolutionSize(); i++)
	{
		solution[i] = r.getNextDouble(MIN_GENERATED_VALUE, MAX_GENERATED_VALUE);
	}

	return solution;
}


double* DiffEvol::solve(int amountOfSeconds, int* errorCode) {
	Random r;
	int genotypeSize = problem->getSolutionSize();
	initializePopulation();
	double* minmaxtable = this->problem->getMinmaxTable();
	Timer t;
	t.startMeasure();
	while (t.stopMeasure() < amountOfSeconds) {
		
		for (int i = 0; i < this->populationSize; i++) {
			double* ind = this->population.get(i);
			double* baseInd = this->population.get(r.getNextInt(0, this->populationSize-1));
			double* addInd0 = this->population.get(r.getNextInt(0, this->populationSize-1));
			double* addInd1 = this->population.get(r.getNextInt(0, this->populationSize-1));

			if (individualsAreDiffrent(ind, baseInd, addInd0, addInd1)) {
				double* indNew = new double[genotypeSize];
				int minmaxOffset = 0;
				for (int geneOffset = 0; geneOffset < genotypeSize; geneOffset++)
				{
					if (r.getNextDouble(0, 1) < CROSSPROB) {
						indNew[geneOffset] = clip(baseInd[geneOffset] + DIFFWEIGHT * (addInd0[geneOffset] - addInd1[geneOffset]),minmaxtable[minmaxOffset], minmaxtable[minmaxOffset+1]);
					}
					else indNew[geneOffset] = ind[geneOffset];
					minmaxOffset += 2;
				}
				
				if (this->problem->getQuality(indNew, errorCode) > this->problem->getQuality(ind, errorCode)) {

					this->population.setValueAt(i,indNew);
					delete[] ind;
				}
				else {
					delete[] indNew;
				}
			}
		}
	}
	delete[] minmaxtable;
	double* sol = getBestResult(errorCode);
	double* solution = new double[problem->getSolutionSize()];
	memcpy(solution, sol, problem->getSolutionSize()*sizeof(double));
	return solution;
}

double* DiffEvol::getBestResult(int* errorCode) {
	double* bestSolution = nullptr;
	double*	currentSolution;

	for (int i = 0; i < this->populationSize; i++)
	{
		currentSolution = this->population.get(i);

		if (this->problem->getQuality(currentSolution, errorCode) > this->problem->getQuality(bestSolution, errorCode)) {
			bestSolution = currentSolution;
		}
	}
	return bestSolution;
}