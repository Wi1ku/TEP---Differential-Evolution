#pragma once
#pragma warning(disable : 4996)
#include <cstdio>
#include "Constants.h"
#include "Matrix.h"
#include "Table.h"
class FileHelper

{
public:
	FileHelper(const char* filename, const char* mode) {
		fileIsLoaded = false;
		this->fileName = filename;
		pFile = fopen(fileName, mode);
		if (pFile != NULL) fileIsLoaded = true;
	}

	~FileHelper() {
		if (fileIsLoaded) {
			fclose(pFile);
		}
	}

	void skipNextLine() {
		if(!(this->IsLoaded())) return;
		char c = NULL;
		while (c != '\n') fscanf(pFile, "%c", &c);
	}

	int getNextParameter() {
		char c;
		int d;
		fscanf(pFile, " %c %i\n", &c, &d);
		return d;
	}

	bool fillMatrixOfDoubles(Matrix<double>& m) {
		if (!(this->IsLoaded())) return false;
		double d;
		char c = NULL;
		for (int i = 0; i < m.getRows(); i++)
		{
			for (int j = 0; j < m.getColumns(); j++)
			{
				fscanf(pFile, "%lf", &d);
				fscanf(pFile, "%c", &c);
				if (c != ';') return false;
				m.set(d, i, j);
			}
		}
		fscanf(pFile, "%c", &c);
		if (c != '\n') return false;
		return true;
	}

	bool fillTableOfDoubles(Table<double>& t) {
		if (!(this->IsLoaded())) return false;
		double d;
		char c = NULL;
		for (int i = 0; i < t.getTableLength(); i++)
		{
			fscanf(pFile, "%lf", &d);
			fscanf(pFile, "%c", &c);
			if (c != ';') return false;
			t.setValueAt(i, d);
		}
		fscanf(pFile, "%c", &c);
		if (c != '\n') return false;
		return true;
	}

	bool fillMinMax(Matrix<double>& min, Matrix<double>& max) {
		if (!(this->IsLoaded())) return true;
		double d;
		char c = NULL;
		for (int i = 0; i < min.getRows(); i++)
		{
			for (int j = 0; j < min.getColumns(); j++)
			{
				fscanf(pFile, "%lf", &d);
				fscanf(pFile, "%c", &c);
				if (c != ';') return false;
				min.set(d, i, j);
				fscanf(pFile, "%lf", &d);
				fscanf(pFile, "%c", &c);
				if (c != ';') return false;
				max.set(d, i, j);
			}
		}
		fscanf(pFile, "%c", &c);
		if (c != '\n' && c != ';' && c!= EOF) return false;
		return true;
	}

	void writeMinMax(Matrix<double>& min, Matrix<double>& max) {
		if (!(this->IsLoaded())) return;
		for (int i = 0; i < min.getRows(); i++)
		{
			for (int j = 0; j < min.getColumns(); j++)
			{
				fprintf(pFile, "%lf ", min.get(i, j));
				fprintf(pFile, "%lf ", max.get(i, j));
			}
		}
		fprintf(pFile, "\n");
	}

	void writeParameterToFile(char param, int i) {
		if (!(this->IsLoaded())) return;
		fprintf(pFile, "%c %i\n", param, i);
	}

	void writeTableToFile(Table<double>& t) {
		if (!(this->IsLoaded())) return;
		for (int i = 0; i < t.getTableLength(); i++)
		{
			fprintf(pFile, "%lf ", t.get(i));
		}
		fprintf(pFile, "\n");
	}

	void writeMatrixToFile(Matrix<double>& m) {
		if (!(this->IsLoaded())) return;
		for (int i = 0; i < m.getRows(); i++)
		{
			for (int j = 0; j < m.getColumns(); j++)
			{
				fprintf(pFile, "%lf ", m.get(i, j));
			}
		}
		fprintf(pFile, "\n");
	}

	void writeLine(const char* txt) {
		if (!(this->IsLoaded())) return;
		fputs(txt, pFile);
		fprintf(pFile, "\n");
	}
	
	double* readDoubleArray(int size) {
		double* d = new double[size];
		double dd;
		char c = NULL;
		for (int i = 0; i < size; i++)
		{
			fscanf(pFile, " %lf", &dd);
			d[i] = dd;
		}
		fscanf(pFile, " %c", &c);
		return d;
	}

	bool IsLoaded() { return this->fileIsLoaded; }


private:
	FILE* pFile;
	const char* fileName;
	bool fileIsLoaded;
};

