#pragma once
#include <iostream>
#include <string>
#include "Constants.h"
#include "Random.h"
using namespace std;

template <typename T>
class Table {
public:
	Table();
	Table(int tableLength);
	Table(const Table& pc_Other);
	~Table();
	int getTableLength();
	bool setNewSize(int newTableLength);
	Table* pc_Clone();
	T get(int index) { return this->pi_table[index]; }
	void setValueAt(int offset, T newVal);
	inline void fillWithRandomDoubles(double a, double b);
	Table operator+(Table& pTable);
	Table operator=(const Table& cOther);
	Table(Table&& pc_Other) noexcept;
	Table& operator=(Table&& other) noexcept;

	void fill(T value);
	void show();



private:
	int tableLength;
	T* pi_table;
	T* copyTable(T* table, int lastIndex, int newTableSize);
};

template <typename T>
Table<T>::Table() {
	this->tableLength = DEFAULT_LENGTH;
	this->pi_table = new T[DEFAULT_LENGTH];
}

template <typename T>
Table<T>::Table(int tableLength) {
	this->tableLength = tableLength;
	this->pi_table = new T[tableLength];
}

template <typename T>
Table<T>::Table(const Table& pc_Other) {
	this->tableLength = pc_Other.tableLength;
	this->pi_table = copyTable(pc_Other.pi_table, this->tableLength, this->tableLength);
}
template <typename T>
Table<T>::~Table() {
	if (this->pi_table != NULL) delete[] this->pi_table;
}

template <typename T>
int Table<T>::getTableLength() {
	return this->tableLength;
}
template <typename T>
bool Table<T>::setNewSize(int newTableLength) {
	T* pi_newTable;
	if (newTableLength < 0) return false;
	if (newTableLength == this->tableLength) return true;
	else if (newTableLength > this->tableLength) {
		pi_newTable = copyTable(this->pi_table, this->tableLength, newTableLength);
	}
	else {
		pi_newTable = copyTable(this->pi_table, newTableLength, newTableLength);
	}
	delete[] pi_table;
	this->tableLength = newTableLength;
	pi_table = pi_newTable;
	return true;
}
template <typename T>
Table<T>* Table<T>::pc_Clone() {
	Table* clone = new Table(*this);
	return clone;
}
template <typename T>
void Table<T>::fill(T value) {
	for (int i = 0; i < this->tableLength; i++) {
		this->pi_table[i] = value++;
	}
}
template <typename T>
void Table<T>::show() {
	for (int i = 0; i < this->tableLength; i++) {
		std::cout << this->pi_table[i] << " ";
	}
	std::cout << endl;
}

template <typename T>
T* Table<T>::copyTable(T* table, int lastIndex, int newTableSize) {
	if (lastIndex > newTableSize) return NULL;
	T* newTable = new T[newTableSize];
	for (int i = 0; i < lastIndex; i++) {
		newTable[i] = table[i];
	}
	return newTable;
}

template <typename T>
void Table<T>::setValueAt(int offset, T newVal) {
	this->pi_table[offset] = newVal;
}
template <typename T>

Table<T> Table<T>::operator+(Table& pTable) {
	Table<T> NewTable(this->tableLength+ pTable.tableLength);
	for (int i = 0; i < this->tableLength; i++) {
		NewTable.pi_table[i] = this->pi_table[i];
	}
	for (int i = this->tableLength; i < NewTable.tableLength; i++) {
		NewTable.pi_table[i] = pTable.pi_table[i - this->tableLength];
	}
	return NewTable;
}


template <typename T>
Table<T> Table<T>::operator=(const Table& pTable) {
	if (this == &pTable) return *this;
	this->tableLength = pTable.tableLength;
	delete[] this->pi_table;
	this->pi_table = copyTable(pTable.pi_table, this->tableLength, this->tableLength);
	return *this;
}

template <typename T>
Table<T>::Table(Table&& other) noexcept {
	pi_table = other.pi_table;
	tableLength = other.tableLength;
	other.pi_table = NULL;
}
template <typename T>
Table<T>& Table<T>::operator=(Table&& other) noexcept {
	if (&other == this) {
		return *this;
	}
	if (this->pi_table != NULL) delete this->pi_table;
	this->pi_table = other.pi_table;
	this->tableLength = other.tableLength;
	other.pi_table = NULL;
	other.tableLength = -1;
	return *this;
}

void Table<double>::fillWithRandomDoubles(double a, double b) {
	Random r;
	for (int i = 0; i < this->tableLength; i++)
	{
		this->pi_table[i] = r.getNextDouble(a, b);
	}
}

