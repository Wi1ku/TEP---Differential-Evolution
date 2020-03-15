#pragma once
#include <cstdio>
#include "Matrix.h"
#include "Table.h"
#include <string.h>
#include "Solution.h"
#include "Problem.h"

class MscnProblem : public Problem
{
public:
	MscnProblem();
	MscnProblem(int d, int f, int m, int s);
	MscnProblem(const char* fileName, int* pError);
	~MscnProblem();

	//gettters
	int getD() { return this->d; }
	int getF() { return this->f; }
	int getM() { return this->m; }
	int getS() { return this->s; }

	double* getxdMin();
	double* getxdMax();
	double* getxfMin();
	double* getxfMax();
	double* getxmMin();
	double* getxmMax();

	//setters, returns false on faliure
	bool setD(int d);
	bool setF(int f);
	bool setM(int m);
	bool setS(int s);
	bool setCD(int value, int d, int f);
	bool setCF(int value, int f, int m);
	bool setCM(int value, int m, int s);
	bool setSD(int value, int d);
	bool setSF(int value, int f);
	bool setSM(int value, int m);
	bool setSS(int value, int s);
	bool setUD(int value, int d);
	bool setUF(int value, int f);
	bool setUM(int value, int m);
	bool setPS(int value, int s);
	bool setxdMin(int value, int d, int f);
	bool setxdMax(int value, int d, int f);
	bool setxfMin(int value, int f, int m);
	bool setxfMax(int value, int f, int m);
	bool setxmMin(int value, int m, int s);
	bool setxmMax(int value, int m, int s);


	double* getMinmaxTable();
	double getQuality(double* &pdSolution, int* pError);						//pError is set to 1 on Error
	bool constraintsSatisfied(double* pdSolution, int* pError);				//pError is set to 1 on Error
	bool saveProblemToFile(const char* fileName);							//returns false on faliure
	double* getSolutionFromFile(const char* fileName);						//returns NULL on faliure
	void print();
	void generateValues();
	int getSolutionSize();
	


private:
	//private fields:
	int d, f, m, s;
	Matrix<double> cd, cf, cm;
	Matrix<double> minxd, minxf, minxm;
	Matrix<double> maxxd, maxxf, maxxm;
	Table<double> sd, sf, sm, ss;
	Table<double> ud, uf, um;
	Table<double> ps;
	double kt, ku, p, z;

	//private methods:
	bool isInBounds(double val, double a, double b) { return ((val >= a) && (val <= b)); };
	int epsilon(double e) { return e > 0; }
	void printMinMax(Matrix<double>& min, Matrix<double>& max);
	bool checkMinMax(Solution s);
	void fixSolution(double* &pdSolution);
	void fixSolutionNaive(double* &pdSolution);
	double clip(double x, double min, double max) {
		if (x < min) return min;
		else if (x > max) return max;
		else return x;
	}

};

