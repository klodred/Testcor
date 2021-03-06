#pragma once
#include <vector>
#include <iostream>
#include <time.h>

using std::vector;
using std::cout;

template <class T>
class Matrix {
private:
	vector<T> matrix;
	int m;
	int n;

public:
	Matrix() { m = 0; n = 0; };

	Matrix(int _m, int _n) : m(_m), n(_n) { this->resize(_m, _n); };

	friend std::ostream& operator<<(std::ostream& os, Matrix<T>& matr) {

		for (int i = 0; i < matr.m; ++i) {

			for (int j = 0; j < matr.n; ++j) {

				os << matr(i, j) << " ";
			}

			os << "\n";
		}

		return os;
	}

	T& operator()(int i, int j) {

		if (-1 < i && i < m && -1 < j && j < n) {

			return matrix[i * n + j];
		}
	}

	void random(int left, int right) {

		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				matrix[i * n + j] = rand() % right + left;
	}

	void random(int size, int left, int right) {

		this->resize(size, size);
		this->random(left, right);
	}

	void resize(int _m, int _n) {

		matrix.resize(_m * _n);
		m = _m;
		n = _n;
	}

	int size_m() { return m; };

	int size_n() { return n; };
};
