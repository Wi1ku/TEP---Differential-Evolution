#pragma once
#include "Problem.h"

class Optimizer
{
public:
	Optimizer() { this->problem = nullptr; };
	Optimizer(Problem* problem) { this->problem = problem; };
	virtual double* solve(int stopCondition, int* errorCode) =  0;

protected:
	Problem* problem;

};

