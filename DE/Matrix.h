#pragma once
#include "Constants.h"
#include <iostream>
#include "Random.h"


template <typename T> class Matrix
{
public:
	Matrix();
	Matrix(int rows, int columns);
	~Matrix();
	Matrix(const Matrix& other);
	int getRows() { return this->rows; }
	int getColumns() { return this->columns; }
	void print();
	void setNewSize(int rows, int columns);
	void set(T val, int i, int j) { this->matrix[i][j] = val; };
	void fill(int x);
	inline void fillWithRandomDoubles(double a, double b);
	T get(int i, int j) { return this->matrix[i][j]; }
	Matrix operator=(const Matrix& other);
	double sumInRow(int row);
	double sumInColumn(int column);
	T* toArray();
	Matrix(Matrix&& pc_Other) noexcept;
	Matrix& operator=(Matrix&& other) noexcept;

private:
	int rows;
	int columns;
	T** matrix = nullptr;
	void copyMartix(T** src, T** &dest, int r, int c);
	void deleteMatrix(T** &m);
	void allocMatrix(T** &matrix, int rows, int columns);
};

template <typename T>
void Matrix<T>::allocMatrix(T** &matrix, int rows, int columns) {
	matrix = new T * [rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new T[columns]();
	}
}

template <typename T>
void Matrix<T>::fill(int x) {
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			this->matrix[i][j] = x;
		}
	}
}
template <typename T>
void Matrix<T>::copyMartix( T** src,T** &dest, int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			dest[i][j] = src[i][j];
		}
	}
}

template <typename T>
void Matrix<T>::deleteMatrix(T** &m) {
	for (int i = 0; i < rows; i++) {
		delete this->matrix[i];
	}
	delete[] this->matrix;
}

template <typename T>
 Matrix<T>::Matrix() {
	rows = DEFAULT_NUMBER_OF_ROWS;
	columns = DEFAULT_NUMBER_OF_COLUMNS;
	allocMatrix(this->matrix, this->rows, this->columns);
}


 template <typename T>
 Matrix<T>::Matrix(int rows, int columns) {
	 this->rows = rows;
	 this->columns = columns;
	 allocMatrix(this->matrix, this->rows, this->columns);
 }

 template <typename T>
 Matrix<T>::~Matrix() {
	 if (this->matrix != nullptr) deleteMatrix(this->matrix);
 }

 template <typename T>
 Matrix<T>::Matrix(const Matrix &other) {
	 this->rows = other.rows;
	 this->columns = other.columns;
	 allocMatrix(this->matrix, this->rows, this->columns);
	 for (int i = 0; i < other.rows; i++) {
		 for (int j = 0; j < other.columns; j++) {
			 this->matrix[i][j] = other.matrix[i][j];
		 }
	 }
 }
 template <typename T>
 Matrix<T>::Matrix(Matrix&& pc_Other) noexcept {
	 this->rows = pc_Other.rows;
	 this->columns = pc_Other.columns;
	 this->matrix = pc_Other.matrix;
	 pc_Other.matrix = nullptr;
 }

 template <typename T>
 Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
	 if (&other == this) {
		 return *this;
	 }
	 if (this->matrix != nullptr) deleteMatrix(this->matrix);
	 this->rows = other.rows;
	 this->columns = other.columns;
	 this->matrix = other.matrix;
	 other.matrix = nullptr;
	 return *this;
 }

  template <typename T>
  void Matrix<T>::setNewSize(int rows, int columns) {
	  Matrix<T> tmp(*this);
	  deleteMatrix(this->matrix);
	  this->rows = rows;
	  this->columns = columns;
	  allocMatrix(this->matrix, this->rows, this->columns);
	  copyMartix(tmp.matrix, this->matrix, tmp.rows, tmp.columns);
  }

  template <typename T>
  Matrix<T> Matrix<T>::operator=(const Matrix& other) {
	  if (this == &other) return *this;
	  deleteMatrix(this->matrix);
	  this->rows = other.rows;
	  this->columns = other.columns;
	  allocMatrix(this->matrix, this->rows, this->columns);
	  copyMartix(other.matrix, this->matrix, other.rows, other.columns);
	  return *this;
  }

  template <typename T>
  double Matrix<T>::sumInRow(int row) {
	  double sum = 0;
	  for (int i = 0; i < this->columns; i++)
	  {
		  sum += this->matrix[row][i];
	  }
	  return sum;
  }

  template <typename T>
  double Matrix<T>::sumInColumn(int column) {
	  double sum = 0;
	  for (int i = 0; i < this->rows; i++)
	  {
		  sum += this->matrix[i][column];
	  }
	  return sum;
  }

  template <typename T>
  T* Matrix<T>::toArray() {
	  T* array = new T[this->rows * this->columns];
	  int k = 0;
	  for (int i = 0; i < rows; i++)
	  {
		  for (int j = 0; j < columns; j++)
		  {
			  array[k++] = this->matrix[i][j];
		  }
	  }
	  return array;
  }

  template <typename T>
  void Matrix<T>::print() {
	  for (int i = 0; i < rows; i++)
	  {
		  for (int j = 0; j < columns; j++)
		  {
			  std::cout << this->matrix[i][j] << " ";
		  }
	  }
	  std::cout << std::endl;
  }


  void Matrix<double>::fillWithRandomDoubles(double a, double b) {
	  Random r;
	  for (int i = 0; i < rows; i++)
	  {
		  for (int j = 0; j < columns; j++)
		  {
			  this->matrix[i][j] = r.getNextDouble(a, b);
		  }
	  }
  }

