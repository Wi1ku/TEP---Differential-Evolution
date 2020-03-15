#pragma once

class Problem {
public:
	virtual ~Problem(){};
	virtual double getQuality(double* &pdSolution, int* pError) = 0;
	virtual int getSolutionSize() = 0;
	virtual double* getMinmaxTable() = 0;
};
