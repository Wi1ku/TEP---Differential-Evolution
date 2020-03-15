#include "Solution.h"


Solution::Solution(double* pdSolution, int d, int f, int m, int s) {
	this->d = d;
	this->f = f;
	this->m = m;
	this->s = s;

	this->xd = Matrix<double>(d, f);
	this->xf = Matrix<double>(f, m);
	this->xm = Matrix<double>(m, s);

	if (!(this->checkSolution(pdSolution))) {
		this->wrong = true;
	}
	else {

		int k = 0;
		for (int i = 0; i < d; i++)
		{
			for (int j = 0; j < f; j++)
			{
				this->xd.set(pdSolution[k++], i, j);
			}

		}
		for (int i = 0; i < f; i++)
		{
			for (int j = 0; j < m; j++)
			{
				this->xf.set(pdSolution[k++], i, j);
			}

		}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < s; j++)
			{
				this->xm.set(pdSolution[k++], i, j);
			}

		}
	}
}


bool Solution::saveSolutionToFile(const char* fileName) {
	FileHelper file(fileName, WRITE);
	if (!(file.IsLoaded())) return false;
	file.writeParameterToFile('D', this->d);
	file.writeParameterToFile('F', this->f);
	file.writeParameterToFile('M', this->m);
	file.writeParameterToFile('S', this->s);
	file.writeLine("xd");
	file.writeMatrixToFile(this->xd);
	file.writeLine("xf");
	file.writeMatrixToFile(this->xf);
	file.writeLine("xm");
	file.writeMatrixToFile(this->xm);
	return true;
}

bool Solution::checkSolution(double* pdSolution) {
	if (pdSolution == NULL) return false;
	for (int i = 0; i < ((this->d * this->f) + (this->f * this->m) + (this->m * this->s)); i++)
	{
		if (pdSolution[i] < 0) return false;
	}
	return true;
}

void Solution::generateRandomValues() {
	this->xd.fillWithRandomDoubles(MIN_GENERATED_VALEUE_IN_XD, MAX_GENERATED_VALEUE_IN_XD);
	this->xf.fillWithRandomDoubles(MIN_GENERATED_VALEUE_IN_XF, MAX_GENERATED_VALEUE_IN_XF);
	this->xm.fillWithRandomDoubles(MIN_GENERATED_VALEUE_IN_XM, MAX_GENERATED_VALEUE_IN_XM);
}

double* Solution::toArray() {
	double* solution = new double[(this->d * this->f) + (this->f * this->m) + (this->m * this->s)];
	double* xd = this->xd.toArray();
	double* xf = this->xf.toArray();
	double* xm = this->xm.toArray();
	int k = 0;
	for (int i = 0; i < (this->d * this->f); i++)
	{
		solution[k++] = xd[i];
	}
	for (int i = 0; i < (this->f * this->m); i++)
	{
		solution[k++] = xf[i];
	}
	for (int i = 0; i < (this->m * this->s); i++)
	{
		solution[k++] = xm[i];
	}
	delete xd;
	delete xf;
	delete xm;
	return solution;

}

void Solution::changeSolution(double* &pdSolution) {
	double* xd = this->xd.toArray();
	double* xf = this->xf.toArray();
	double* xm = this->xm.toArray();
	int k = 0;
	for (int i = 0; i < (this->d * this->f); i++)
	{
		pdSolution[k++] = xd[i];
	}
	for (int i = 0; i < (this->f * this->m); i++)
	{
		pdSolution[k++] = xf[i];
	}
	for (int i = 0; i < (this->m * this->s); i++)
	{
		pdSolution[k++] = xm[i];
	}
	delete xd;
	delete xf;
	delete xm;
}
	