#pragma once
#include "Matrix.h"
#include "FileHelper.h"
#include "Constants.h"

class Solution
{
public:
	Solution(double* pdSolution, int d, int f, int m, int s);
	void generateRandomValues();
	bool saveSolutionToFile(const char* fileName);
	bool isWrong() { return this->wrong; }
	Matrix<double> xd, xf, xm;
	double* toArray();
	void changeSolution(double* &pdSolution);

private:
	int d, f, m, s;
	
	bool wrong;
	bool checkSolution(double* pdSolution);
};

