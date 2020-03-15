#include "MscnProblem.h"
#include "FileHelper.h"

//constructors
MscnProblem::MscnProblem() {
	this->d = DEFAULT_D_VALUE;
	this->f = DEFAULT_F_VALUE;
	this->m = DEFAULT_M_VALUE;
	this->s = DEFAULT_S_VALUE;

	this->cd = Matrix<double>(DEFAULT_D_VALUE, DEFAULT_F_VALUE);
	this->cf = Matrix<double>(DEFAULT_F_VALUE, DEFAULT_M_VALUE);
	this->cm = Matrix<double>(DEFAULT_M_VALUE, DEFAULT_S_VALUE);

	this->minxd = Matrix<double>(DEFAULT_D_VALUE, DEFAULT_F_VALUE);
	this->minxf = Matrix<double>(DEFAULT_F_VALUE, DEFAULT_M_VALUE);
	this->minxm = Matrix<double>(DEFAULT_M_VALUE, DEFAULT_S_VALUE);

	this->maxxd = Matrix<double>(DEFAULT_D_VALUE, DEFAULT_F_VALUE);
	this->maxxf = Matrix<double>(DEFAULT_F_VALUE, DEFAULT_M_VALUE);
	this->maxxm = Matrix<double>(DEFAULT_M_VALUE, DEFAULT_S_VALUE);


	this->sd = Table<double>(DEFAULT_D_VALUE);
	this->sf = Table<double>(DEFAULT_F_VALUE);
	this->sm = Table<double>(DEFAULT_M_VALUE);
	this->ss = Table<double>(DEFAULT_S_VALUE);

	this->ud = Table<double>(DEFAULT_D_VALUE);
	this->uf = Table<double>(DEFAULT_F_VALUE);
	this->um = Table<double>(DEFAULT_M_VALUE);

	this->ps = Table<double>(DEFAULT_S_VALUE);
}


MscnProblem::MscnProblem(int d, int f, int m, int s) {
	this->d = d;
	this->f = f;
	this->m = m;
	this->s = s;

	this->cd = Matrix<double>(d, f);
	this->cf = Matrix<double>(f, m);
	this->cm = Matrix<double>(m, s);

	this->minxd = Matrix<double>(d, f);
	this->minxf = Matrix<double>(f, m);
	this->minxm = Matrix<double>(m, s);

	this->maxxd = Matrix<double>(d, f);
	this->maxxf = Matrix<double>(f, m);
	this->maxxm = Matrix<double>(m, s);

	this->sd = Table<double>(d);
	this->sf = Table<double>(f);
	this->sm = Table<double>(m);
	this->ss = Table<double>(s);

	this->ud = Table<double>(d);
	this->uf = Table<double>(f);
	this->um = Table<double>(m);

	this->ps = Table<double>(s);

	this->minxd.fill(MINXD_DEFAULT_VALUES);
	this->minxf.fill(MINXF_DEFAULT_VALUES);
	this->minxm.fill(MINXM_DEFAULT_VALUES);
	this->maxxd.fill(MAXXD_DEFAULT_VALUES);
	this->maxxf.fill(MAXXF_DEFAULT_VALUES);
	this->maxxm.fill(MAXXM_DEFAULT_VALUES);

	this->generateValues();

}




MscnProblem::MscnProblem(const char* fileName, int* pError) {
	*pError = 0;
	FileHelper file(fileName, READ);
	if (!(file.IsLoaded())) {
		*pError = 1;
		this->d = DEFAULT_D_VALUE;
		this->f = DEFAULT_F_VALUE;
		this->m = DEFAULT_M_VALUE;
		this->s = DEFAULT_S_VALUE;

		this->cd = Matrix<double>(DEFAULT_D_VALUE, DEFAULT_F_VALUE);
		this->cf = Matrix<double>(DEFAULT_F_VALUE, DEFAULT_M_VALUE);
		this->cm = Matrix<double>(DEFAULT_M_VALUE, DEFAULT_S_VALUE);

		this->minxd = Matrix<double>(DEFAULT_D_VALUE, DEFAULT_F_VALUE);
		this->minxf = Matrix<double>(DEFAULT_F_VALUE, DEFAULT_M_VALUE);
		this->minxm = Matrix<double>(DEFAULT_M_VALUE, DEFAULT_S_VALUE);

		this->maxxd = Matrix<double>(DEFAULT_D_VALUE, DEFAULT_F_VALUE);
		this->maxxf = Matrix<double>(DEFAULT_F_VALUE, DEFAULT_M_VALUE);
		this->maxxm = Matrix<double>(DEFAULT_M_VALUE, DEFAULT_S_VALUE);

		this->sd = Table<double>(DEFAULT_D_VALUE);
		this->sf = Table<double>(DEFAULT_F_VALUE);
		this->sm = Table<double>(DEFAULT_M_VALUE);
		this->ss = Table<double>(DEFAULT_S_VALUE);

		this->ud = Table<double>(DEFAULT_D_VALUE);
		this->uf = Table<double>(DEFAULT_F_VALUE);
		this->um = Table<double>(DEFAULT_M_VALUE);

		this->ps = Table<double>(DEFAULT_S_VALUE);
	}
	else {
		this->d = file.getNextParameter();
		this->f = file.getNextParameter();
		this->m = file.getNextParameter();
		this->s = file.getNextParameter();

		this->cd = Matrix<double>(this->d, this->f);
		this->cf = Matrix<double>(this->f, this->m);
		this->cm = Matrix<double>(this->m, this->s);

		this->minxd = Matrix<double>(d, f);
		this->minxf = Matrix<double>(f, m);
		this->minxm = Matrix<double>(m, s);

		this->maxxd = Matrix<double>(d, f);
		this->maxxf = Matrix<double>(f, m);
		this->maxxm = Matrix<double>(m, s);


		this->sd = Table<double>(this->d);
		this->sf = Table<double>(this->f);
		this->sm = Table<double>(this->m);
		this->ss = Table<double>(this->s);

		this->ud = Table<double>(this->d);
		this->uf = Table<double>(this->f);
		this->um = Table<double>(this->m);

		this->ps = Table<double>(this->s);

		file.skipNextLine();
		if (!file.fillTableOfDoubles(this->sd)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillTableOfDoubles(this->sf)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillTableOfDoubles(this->sm)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillTableOfDoubles(this->ss)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillMatrixOfDoubles(this->cd)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillMatrixOfDoubles(this->cf)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillMatrixOfDoubles(this->cm)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillTableOfDoubles(this->ud)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillTableOfDoubles(this->uf)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillTableOfDoubles(this->um)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillTableOfDoubles(this->ps)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillMinMax(this->minxd, this->maxxd)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillMinMax(this->minxf, this->maxxf)) { *pError = 1; return; };
		file.skipNextLine();
		if(!file.fillMinMax(this->minxm, this->maxxm)) { *pError = 1; return; };
	}

}
//destructor
MscnProblem::~MscnProblem() {}

//setters, return false on faliure

bool MscnProblem::setD(int d){
	if (d < 0) return false;
	this->d = d;
	this->cd.setNewSize(this->d, this->f);
	this->sd.setNewSize(this->d);
	this->ud.setNewSize(this->d);
	this->minxd.setNewSize(this->d, this->f);
	this->maxxd.setNewSize(this->d, this->f);

	return true;
}

bool MscnProblem::setF(int f) {
	if (f < 0) return false;
	this->f = f;
	this->cd.setNewSize(this->d, this->f);
	this->minxd.setNewSize(this->d, this->f);
	this->maxxd.setNewSize(this->d, this->f);
	this->cf.setNewSize(this->f, this->m);
	this->minxf.setNewSize(this->f, this->m);
	this->maxxf.setNewSize(this->f, this->m);
	this->sf.setNewSize(this->f);
	this->uf.setNewSize(this->f);
	return true;
}

bool MscnProblem::setM(int m) {
	if (m < 0) return false;
	this->m = m;
	this->cf.setNewSize(this->f, this->m);
	this->minxf.setNewSize(this->f, this->m);
	this->maxxf.setNewSize(this->f, this->m);
	this->cm.setNewSize(this->m, this->s);
	this->minxm.setNewSize(this->m, this->s);
	this->maxxm.setNewSize(this->m, this->s);
	this->sm.setNewSize(this->m);
	this->um.setNewSize(this->m);
	return true;
}

bool MscnProblem::setS(int s) {
	if (s < 0) return false;
	this->cm.setNewSize(this->m, this->s);
	this->minxm.setNewSize(this->m, this->s);
	this->maxxm.setNewSize(this->m, this->s);
	this->s = s;
	this->ss.setNewSize(this->s);
	this->ps.setNewSize(this->s);
	return true;
}

bool MscnProblem::setCD(int value, int d, int f) {
	if (value < 0 || !isInBounds(d, 0, this->d) || !isInBounds(f, 0, this->f)) return false;
	this->cd.set(value, d, f);
	return true;
}

bool MscnProblem::setCF(int value, int f, int m) {
	if (value < 0 || !isInBounds(f, 0, this->f) || !isInBounds(m, 0, this->m)) return false;
	this->cf.set(value, f, m);
	return true;
}

bool MscnProblem::setCM(int value, int m, int s) {
	if (value < 0 || !isInBounds(m, 0, this->m) || !isInBounds(s, 0, this->s)) return false;
	this->cm.set(value, m, s);
	return true;
}

bool MscnProblem::setSD(int value, int d) {
	if (value < 0 || !isInBounds(d, 0, this->d)) return false;
	this->sd.setValueAt(d, value);
	return true;
}

bool MscnProblem::setSF(int value, int f) {
	if (value < 0 || !isInBounds(f, 0, this->f)) return false;
	this->sf.setValueAt(f, value);
	return true;
}

bool MscnProblem::setSM(int value, int m) {
	if (value < 0 || !isInBounds(m, 0, this->m)) return false;
	this->sm.setValueAt(m, value);
	return true;
}

bool MscnProblem::setSS(int value, int s) {
	if (value < 0 || !isInBounds(s, 0, this->s)) return false;
	this->ss.setValueAt(s, value);
	return true;
}

bool MscnProblem::setUD(int value, int d) {
	if (value < 0 || !isInBounds(d, 0, this->d)) return false;
	this->ud.setValueAt(d, value);
	return true;
}

bool MscnProblem::setUF(int value, int f) {
	if (value < 0 || !isInBounds(f, 0, this->f)) return false;
	this->uf.setValueAt(f, value);
	return true;
}

bool MscnProblem::setUM(int value, int m) {
	if (value < 0 || !isInBounds(m, 0, this->m)) return false;
	this->um.setValueAt(m, value);
	return true;
}

bool MscnProblem::setPS(int value, int s) {
	if (value < 0 || !isInBounds(s, 0, this->s)) return false;
	this->ps.setValueAt(s, value);
	return true;
}

bool MscnProblem::setxdMin(int value, int d, int f) {
	if (value < 0 || !isInBounds(d, 0, this->d) || !isInBounds(f, 0, this->f)) return false;
	this->minxd.set(value, d, f);
	return true;
}

bool MscnProblem::setxfMin(int value, int f, int m) {
	if (value < 0 || !isInBounds(f, 0, this->f) || !isInBounds(m, 0, this->m)) return false;
	this->minxf.set(value, f, m);
	return true;
}

bool MscnProblem::setxmMin(int value, int m, int s) {
	if (value < 0 || !isInBounds(m, 0, this->m) || !isInBounds(s, 0, this->s)) return false;
	this->minxm.set(value, m, s);
	return true;
}

bool MscnProblem::setxdMax(int value, int d, int f) {
	if (value < 0 || !isInBounds(d, 0, this->d) || !isInBounds(f, 0, this->f)) return false;
	this->maxxd.set(value, d, f);
	return true;
}

bool MscnProblem::setxfMax(int value, int f, int m) {
	if (value < 0 || !isInBounds(f, 0, this->f) || !isInBounds(m, 0, this->m)) return false;
	this->maxxf.set(value, f, m);
	return true;
}

bool MscnProblem::setxmMax(int value, int m, int s) {
	if (value < 0 || !isInBounds(m, 0, this->m) || !isInBounds(s, 0, this->s)) return false;
	this->maxxm.set(value, m, s);
	return true;
}




bool MscnProblem::constraintsSatisfied(double* pdSolution, int *pError) {
	*pError = 0;
	Solution s(pdSolution, this->d, this->f, this->m, this->s);
	if(s.isWrong() || !(this->checkMinMax(s))){
		*pError = 1;
		return false;
		}

	/*Sumaryczna iloœæ surowca zamówiona u
		danego dostawcy nie mo¿e przekroczyæ
		jego mocy produkcyjnych*/
	for (int i = 0; i < this->d; i++)
	{
		if(!(s.xd.sumInRow(i) <= this->sd.get(i))) return false;
	}

	/*Sumaryczna iloœæ produktów zamówiona
		w danej fabryce nie mo¿e przekroczyæ jej
		mocy produkcyjnych*/
	for (int i = 0; i < this->f; i++)
	{
		if (!(s.xf.sumInRow(i) <= this->sf.get(i))) return false;
	}

	/*Sumaryczna iloœæ produktów zamówiona
		pobierana z danego magazynu nie mo¿e
		przekroczyæ jego pojemnoœci*/

	for (int i = 0; i < this->m; i++)
	{
		if (!(s.xm.sumInRow(i) <= this->sm.get(i))) return false;
	}

	/*Sumaryczna iloœæ produktów dostarczana
		do danego sklepu nie mo¿e przekroczyæ
			zapotrzebowania rynkowego dla tego
			sklepu*/

	for (int i = 0; i < this->s; i++)
	{
		if (!(s.xm.sumInColumn(i) <= this->ss.get(i))) return false;
	}

	/*Suma surowców od dostawców
		wchodz¹cych do jednej fabryki f, nie
		mo¿e byæ mniejsza ni¿ suma produktów
		wychodz¹cych z tej fabryki f.
		Innymi s³owy, fabryka musi dostaæ
		wystarczaj¹c¹ iloœæ surowca, ¿eby
		wyprodukowaæ wystarczaj¹c¹ iloœæ
		produktów.*/

	for (int i = 0; i < this->f; i++)
	{
		if (!(s.xd.sumInColumn(i) >= s.xf.sumInRow(i))) return false;
	}

	/*Suma wszystkich produktów
		dostarczanych do jednego centrum
		dystrybucyjnego m nie mo¿e byæ
		mniejsza ni¿ suma wszystkich produktów
		dostarczanych z tego centrum
		dystrybucyjnego m do sklepów.
		Innymi s³owy magazyn musi otrzymaæ z
		fabryk wystarczaj¹c¹ iloœæ produktów,
		¿eby móc dostarczyæ je do sklepów.*/
	for (int i = 0; i < this->m; i++)
	{
		if(!(s.xf.sumInColumn(i) >= s.xm.sumInRow(i))) return false;
	}

	return true;
}

double* MscnProblem::getxdMin() {
	return this->minxd.toArray();
}

double* MscnProblem::getxdMax() {
	return this->maxxd.toArray();
}

double* MscnProblem::getxfMin() {
	return this->minxf.toArray();
}

double* MscnProblem::getxfMax() {
	return this->maxxf.toArray();
}

double* MscnProblem::getxmMin() {
	return this->minxm.toArray();
}

double* MscnProblem::getxmMax() {
	return this->maxxm.toArray();
}


double MscnProblem::getQuality(double* &pdSolution, int* pError) {
	if (pdSolution == nullptr) return 0;
	*pError = 0;
	if (!this->constraintsSatisfied(pdSolution, pError)) this->fixSolution(pdSolution);
	if (!this->constraintsSatisfied(pdSolution, pError)) this->fixSolutionNaive(pdSolution);
	Solution s(pdSolution, this->d, this->f, this->m, this->s);
	if (s.isWrong()) {
		*pError = 1;
		return 0;
	}

	

	//Kt sum
	this->kt = 0;
	for (int i = 0; i < this->d; i++)
	{
		for (int j = 0; j < this->f; j++) {
			kt += (this->cd.get(i, j) * s.xd.get(i, j));
		}
	}

	for (int i = 0; i < this->f; i++)
	{
		for (int j = 0; j < this->m; j++) {
			kt += (this->cf.get(i, j) * s.xf.get(i, j));
		}
	}

	for (int i = 0; i < this->m; i++)
	{
		for (int j = 0; j < this->s; j++) {
			kt += (this->cm.get(i, j) * s.xm.get(i, j));
		}
	}

	//Ku sum;
	this->ku = 0;
	for (int i = 0; i < this->d; i++)
	{
		ku += epsilon(s.xd.sumInRow(i)) * this->ud.get(i);
	}

	for (int i = 0; i < this->f; i++)
	{
		ku += epsilon(s.xf.sumInRow(i)) * this->uf.get(i);
	}

	for (int i = 0; i < this->m; i++)
	{
		ku += epsilon(s.xm.sumInRow(i)) * this->um.get(i);
	}

	//p sum
	this->p = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < this->s; j++)
		{
			p += (ps.get(j) * s.xm.get(i, j));
		}
	}
  //z sum
	this->z = p - kt - ku;

	return z;
}

bool MscnProblem::saveProblemToFile(const char* fileName) {
	FileHelper file(fileName, WRITE);
	if (!(file.IsLoaded())) return false;
	file.writeParameterToFile('D', this->d);
	file.writeParameterToFile('F', this->f);
	file.writeParameterToFile('M', this->m);
	file.writeParameterToFile('S', this->s);
	file.writeLine("sd");
	file.writeTableToFile(this->sd);
	file.writeLine("sf");
	file.writeTableToFile(this->sf);
	file.writeLine("sm");
	file.writeTableToFile(this->sm);
	file.writeLine("ss");
	file.writeTableToFile(this->ss);

	file.writeLine("cd");
	file.writeMatrixToFile(this->cd);
	file.writeLine("cf");
	file.writeMatrixToFile(this->cf);
	file.writeLine("cm");
	file.writeMatrixToFile(this->cm);

	file.writeLine("ud");
	file.writeTableToFile(this->ud);
	file.writeLine("uf");
	file.writeTableToFile(this->uf);
	file.writeLine("um");
	file.writeTableToFile(this->um);
	file.writeLine("ps");
	file.writeTableToFile(this->ps);
	file.writeLine("xdminmax");
	file.writeMinMax(this->minxd, this->maxxd);
	file.writeLine("xfminmax");
	file.writeMinMax(this->minxf, this->maxxf);
	file.writeLine("xmminmax");
	file.writeMinMax(this->minxm, this->maxxm);
	return true;
}

double* MscnProblem::getSolutionFromFile(const char* fileName) {
	FileHelper file(fileName, READ);
	if (!file.IsLoaded()) return NULL;
	int D = file.getNextParameter();
	int F = file.getNextParameter();
	int M = file.getNextParameter();
	int S = file.getNextParameter();
	if ((D != this->d) && (F != this->f) && (M != this->m) && (S != this->s)) return NULL;
	else {
		double* soution = new double[(this->d * this->f) + (this->f * this->m) + (this->m * this->s)];
		file.skipNextLine();
		double* xd = file.readDoubleArray(this->d * this->f);
		file.skipNextLine();
		double* xf = file.readDoubleArray(this->f * this->m);
		file.skipNextLine();
		double* xm = file.readDoubleArray(this->m * this->s);
		int k = 0;
		for (int i = 0; i < (this->d * this->f); i++)
		{
			soution[k++] = xd[i];
		}
		for (int i = 0; i < (this->f * this->m); i++)
		{
			soution[k++] = xf[i];
		}
		for (int i = 0; i < (this->m * this->s); i++)
		{
			soution[k++] = xm[i];
		}
		delete xd;
		delete xf;
		delete xm;
		return soution;
	}
}



void MscnProblem::print() {
	std::cout <<  "D " << this->d << endl;
	std::cout << "F " << this->f << endl;
	std::cout << "M " << this->m << endl;
	std::cout << "S " << this->s << endl;

	std::cout << "sd" << endl;
	this->sd.show();
	std::cout << "sf" << endl;
	this->sf.show();
	std::cout << "sm" << endl;
	this->sm.show();
	std::cout << "ss" << endl;
	this->ss.show();

	std::cout << "cd" << endl;
	this->cd.print();
	std::cout << "cf" << endl;
	this->cf.print();
	std::cout << "cm" << endl;
	this->cm.print();

	std::cout << "ud" << endl;
	this->ud.show();
	std::cout << "uf" << endl;
	this->uf.show();
	std::cout << "um" << endl;
	this->um.show();
	std::cout << "ps" << endl;
	this->ps.show();
	std::cout << "xdminmax" << endl;
	printMinMax(this->minxd, this->maxxd);
	std::cout << "xfminmax" << endl;
	printMinMax(this->minxf, this->maxxf);
	std::cout << "xmminmax" << endl;
	printMinMax(this->minxm, this->maxxm);
	
}

void MscnProblem::printMinMax(Matrix<double>& min, Matrix<double>& max) {
	for (int i = 0; i < min.getRows(); i++)
	{
		for (int j = 0; j < min.getColumns(); j++)
		{
			std::cout << min.get(i, j) << " " << max.get(i, j) << " ";
		}
	}
	std::cout << endl;
}

bool MscnProblem::checkMinMax(Solution s) {
	for (int i = 0; i < minxd.getRows(); i++)
	{
		for (int j = 0; j < minxd.getColumns(); j++)
		{
			if(!(isInBounds(s.xd.get(i,j),this->minxd.get(i,j), this->maxxd.get(i,j)))) return false;
		}
	}
	for (int i = 0; i < minxf.getRows(); i++)
	{
		for (int j = 0; j < minxf.getColumns(); j++)
		{
			if (!(isInBounds(s.xf.get(i, j), this->minxf.get(i, j), this->maxxf.get(i, j)))) return false;
		}
	}
	for (int i = 0; i < minxm.getRows(); i++)
	{
		for (int j = 0; j < minxm.getColumns(); j++)
		{
			if (!(isInBounds(s.xm.get(i, j), this->minxm.get(i, j), this->maxxm.get(i, j)))) return false;
		}
	}
	return true;
}

void MscnProblem::generateValues() {
	this->cd.fillWithRandomDoubles(MIN_GENERATED_VALUE_IN_CD, MAX_GENERATED_VALUE_IN_CD);
	this->cf.fillWithRandomDoubles(MIN_GENERATED_VALUE_IN_CF, MAX_GENERATED_VALUE_IN_CF);
	this->cm.fillWithRandomDoubles(MIN_GENERATED_VALUE_IN_CM, MAX_GENERATED_VALUE_IN_CM);
	this->ud.fillWithRandomDoubles(MIN_GENERATED_VALUE_IN_UD, MAX_GENERATED_VALUE_IN_UD);
	this->uf.fillWithRandomDoubles(MIN_GENERATED_VALUE_IN_UF, MAX_GENERATED_VALUE_IN_UF);
	this->um.fillWithRandomDoubles(MIN_GENERATED_VALUE_IN_UM, MAX_GENERATED_VALUE_IN_UM);
	this->sd.fillWithRandomDoubles(MIN_GENERATED_VALUE_IN_SD, MAX_GENERATED_VALUE_IN_SD);
	this->sf.fillWithRandomDoubles(MIN_GENERATED_VALUE_IN_SF, MAX_GENERATED_VALUE_IN_SF);
	this->sm.fillWithRandomDoubles(MIN_GENERATED_VALUE_IN_SM, MAX_GENERATED_VALUE_IN_SM);
	this->ss.fillWithRandomDoubles(MIN_GENERATED_VALUE_IN_SS, MAX_GENERATED_VALUE_IN_SS);
	this->ps.fillWithRandomDoubles(MIN_GENERATED_VALUE_IN_PS, MAX_GENERATED_VALUE_IN_PS);
}

double* MscnProblem::getMinmaxTable() {
	double* minmaxtable = new double[2*((this->d * this->f) + (this->f * this->m) + (this->m * this->s))];
	int k = 0;
	double* minxd = this->minxd.toArray();
	double* maxxd = this->maxxd.toArray();
	for (int i = 0; i < (this->d*this->f); i++)
	{
		minmaxtable[k++] = minxd[i];
		minmaxtable[k++] = maxxd[i];
	}
	delete[] minxd;
	delete[] maxxd;

	double* minxf = this->minxf.toArray();
	double* maxxf = this->maxxf.toArray();
	for (int i = 0; i <  (this->f * this->m); i++)
	{
		minmaxtable[k++] = minxf[i];
		minmaxtable[k++] = maxxf[i];
	}
	delete[] minxf;
	delete[] maxxf;

	double* minxm = this->minxm.toArray();
	double* maxxm = this->maxxm.toArray();
	for (int i = 0; i < (this->m * this->s); i++)
	{
		minmaxtable[k++] = minxm[i];
		minmaxtable[k++] = maxxm[i];
	}
	delete[] minxm;
	delete[] maxxm;
	return minmaxtable;
}

int MscnProblem::getSolutionSize() {
	return (this->d * this->f) + (this->f * this->m) + (this->m * this->s);
}


void MscnProblem::fixSolution(double* &pdSolution) {
	Solution s(pdSolution, this->d, this->f, this->m, this->s);

	//const 1

	for (int i = 0; i < this->d; i++)
	{
		double s1 = s.xd.sumInRow(i);
		double s2 = this->sd.get(i);
		if (s1 > s2) {
			double diff = s1 - this->sd.get(i);
			diff = diff / this->f;
			for (int j = 0; j < this->f; j++)
			{
				s.xd.set(clip(s.xd.get(i, j) - diff, this->minxd.get(i, j), this->maxxd.get(i, j)), i, j);
			}
		}
	}

	//const 2
	for (int i = 0; i < this->f; i++)
	{
		double s1 = s.xf.sumInRow(i);
		double s2 = this->sf.get(i);
		if (s1 > s2) {
			double diff = s1 - this->sf.get(i);
			diff = (diff / this->m);
			for (int j = 0; j < this->m; j++)
			{
				s.xf.set(clip(s.xf.get(i, j) - diff, this->minxf.get(i, j), this->maxxf.get(i, j)), i, j);
			}
		}
	}

	//const 3
	for (int i = 0; i < this->m; i++)
	{
		double s1 = s.xm.sumInRow(i);
		double s2 = this->sm.get(i);
		if (s1 > s2) {
			double diff = s1 - this->sm.get(i);
			diff = (diff / this->s);
			for (int j = 0; j < this->s; j++)
			{
				s.xm.set(clip(s.xm.get(i, j) - diff, this->minxm.get(i, j), this->maxxm.get(i, j)), i, j);
			}
		}
	}

	//const 4
	for (int i = 0; i < this->s; i++)
	{
		double s1 = s.xm.sumInColumn(i);
		double s2 = this->ss.get(i);
		if (s1 > s2) {
			double diff = s1 - s2;
			diff = (diff / this->m);
			for (int j = 0; j < this->m; j++)
			{
				s.xm.set(clip(s.xm.get(j, i) - diff, this->minxm.get(j, i), this->maxxm.get(j, i)), j, i);
			}
		}
	}

	//const 5
	for (int i = 0; i < this->f; i++)
	{
		double s1 = s.xd.sumInColumn(i);
		double s2 = s.xf.sumInRow(i);
		if (s1 < s2) {
			double diff = s2 - s1;
			diff = (diff / this->m);
			for (int j = 0; j < this->m; j++)
			{
				s.xf.set(clip(s.xf.get(i, j) - diff, this->minxf.get(i, j), this->maxxf.get(i, j)), i, j);
			}
		}
	}

	//const 6
	for (int i = 0; i < this->m; i++)
	{
		double s1 = s.xf.sumInColumn(i);
		double s2 = s.xm.sumInRow(i);
		if (s1  < s2) {
			double diff = s2 - s1;
			diff = (diff / this->s);
			for (int j = 0; j < this->s; j++)
			{
				s.xm.set(clip(s.xm.get(i, j) - diff, this->minxm.get(i, j), this->maxxm.get(i, j)), i, j);
			}
		}
	}
	s.changeSolution(pdSolution);

}


void MscnProblem::fixSolutionNaive(double*& pdSolution) {

	Solution s(pdSolution, this->d, this->f, this->m, this->s);

	//const 1

	for (int i = 0; i < this->d; i++)
	{
		while (s.xd.sumInRow(i) > this->sd.get(i)) {
			for (int j = 0;  j < this->f;  j++)
			{
				s.xd.set(clip(s.xd.get(i, j) - REDUCE_VALUE, this->minxd.get(i, j), this->maxxd.get(i, j)),i,j);
			}
		}
	}

	//const 2
	for (int i = 0; i < this->f; i++)
	{
		while (s.xf.sumInRow(i) > this->sf.get(i)) {
			for (int j = 0; j < this->m; j++)
			{
				s.xf.set(clip(s.xf.get(i, j) - REDUCE_VALUE, this->minxf.get(i, j), this->maxxf.get(i, j)), i, j);
			}
		}
	}

	//const 3
	for (int i = 0; i < this->m; i++)
	{
		while (s.xm.sumInRow(i) > this->sm.get(i)) {
			for (int j = 0; j < this->s; j++)
			{
				s.xm.set(clip(s.xm.get(i, j) - REDUCE_VALUE, this->minxm.get(i, j), this->maxxm.get(i, j)), i, j);
			}
		}
	}

	//const 4
	for (int i = 0; i < this->s; i++)
	{
		while (s.xm.sumInColumn(i) > this->ss.get(i)) {
			for (int j = 0; j < this->m; j++)
			{
				s.xm.set(clip(s.xm.get(j, i) - REDUCE_VALUE, this->minxm.get(j, i), this->maxxm.get(j, i)), j, i);
			}
		}
	}

	//const 5
	for (int i = 0; i < this->f; i++)
	{
		while (s.xd.sumInColumn(i) < s.xf.sumInRow(i)) {
			for (int j = 0; j < this->m; j++)
			{
				s.xf.set(clip(s.xf.get(i, j) - REDUCE_VALUE, this->minxf.get(i, j), this->maxxf.get(i, j)), i, j);
			}
		}
	}

	//const 6
	for (int i = 0; i < this->m; i++)
	{
		while (s.xf.sumInColumn(i) < s.xm.sumInRow(i)) {
			for (int j = 0; j < this->s; j++)
			{
				s.xm.set(clip(s.xm.get(i, j) - REDUCE_VALUE, this->minxm.get(i, j), this->maxxm.get(i, j)), i, j);
			}
		}
	}
	s.changeSolution(pdSolution);
}