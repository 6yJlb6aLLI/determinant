#include <cstdio>
#include <cmath>
#include <ctime>
#include <iostream>
using namespace std;

class Mtrx {
public:
	// конструктор через задание размера
	Mtrx(int _size) {
		size = _size;
		x = new double* [size];
		for (int i = 0; i < size; i++) {
			x[i] = new double[size];
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				x[i][j] = 0;
			}
		}
	}
	Mtrx(Mtrx& matrix) {//оператор копирования
		x = new double* [size];
		for (int i = 0; i < size; i++) {
			x[i] = new double[size];
		}

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				x[i][j] = matrix.x[i][j];
			}
		}
	}
	Mtrx& operator=(const Mtrx& matrix1) {//оператор равно
		if (this == &matrix1)
			return *this; // присвоение самому себе, ничего делать не надо

		for (int i = 0; i < size; i++) {
			delete[] x[i];
		}
		delete[] x;

		x = new double* [size];
		for (int i = 0; i < size; i++) {
			x[i] = new double[size];
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				x[i][j] = matrix1.x[i][j];
			}
		}
		return *this;
	}


	// деструктор
	~Mtrx() {
		for (int i = 0; i < size; i++) {
			delete[] x[i];
		}
		delete[] x;
	}
	double det();
	friend std::ostream& operator<< (std::ostream& out, const Mtrx& mtrx);//вывод
	void setValue(int a, int b, double l) {
		x[a][b] = l;
	}

private:
	int size = 2;
	double** x;
	int search(int n, double what, bool match, unsigned int& uI, unsigned int& uJ, unsigned int starti, unsigned int startj);
	void swapcolumns(int n, unsigned int x1, unsigned int x2);
	void swaprows(int n, unsigned int x1, unsigned int x2);

};
// реализация методов класса
int Mtrx::search(int n, double what, bool match, unsigned int& uI, unsigned int& uJ, unsigned int starti, unsigned int startj) {
	if (!n) return 0;
	if ((starti >= n) || (startj >= n)) return 0;
	for (unsigned int i = starti; i < n; i++)
		for (unsigned int j = startj; j < n; j++) {
			if (match == true) {
				if (x[i][i] == what) {
					uI = i; uJ = j; return 1;
				}
			}
			else if (x[i][j] != what) {
				uI = i; uJ = j; return 1;
			}
		}
	return 0;
}
void Mtrx::swaprows(int n, unsigned int x1, unsigned int x2) {
	if (!n) return;
	if ((x1 >= n) || (x2 >= n) || (x1 == x2)) return;
	double tmp;
	for (unsigned int l = 0; l < n; x++) {
		tmp = x[x1][l];
		x[x1][l] = x[x2][l];
		x[x2][l] = tmp;
	}
	return;
}

void Mtrx::swapcolumns(int n, unsigned int x1, unsigned int x2) {
	if (!n) return;
	if ((x1 >= n) || (x2 >= n) || (x1 == x2)) return;
	double tmp;
	for (unsigned int l = 0; l < n; l++) {
		tmp = x[l][x1];
		x[l][x1] = x[l][x2];
		x[l][x2] = tmp;
	}
	return;
}

double Mtrx::det() {
	unsigned int m = size;
	if (m == 0) return 0;
	if (m == 1) return x[0][0];
	if (m == 2) return (x[0][0] * x[1][1] - x[1][0] * x[0][1]);
	bool sign = false;
	double det = 1;
	double tmp;
	unsigned int z, y;
	for (unsigned int i = 0; i < size; i++) {
		if (x[i][i] == 0) {
			if (!search(size, 0, false, y, z, i, i)) return 0;
			if (i != y) {
				swaprows(size, i, y);
				sign = !sign;
			}
			if (i != z) {
				swapcolumns(size, i, z);
				sign = !sign;
			}
		}
		det *= x[i][i];
		tmp = x[i][i];
		for (z = i; z < m; z++) {
			x[i][z] = x[i][z] / tmp;
		}
		for (y = i + 1; y < size; y++) {
			tmp = x[y][i];
			for (z = i; z < m; z++)
				x[y][z] -= (x[i][z] * tmp);
		}
	}
	if (sign) return det * (-1);
	return det;
}
std::ostream& operator<< (std::ostream& out, const Mtrx& matrix) {//вывод

	for (int i = 0; i < matrix.size; i++) {
		for (int j = 0; j < matrix.size; j++) {
			out << matrix.x[i][j] << " ";
		}
		out << "\n";
	}
	return out;
}



int main() {
	int n;
	setlocale(LC_ALL, "rus");
	cout << "введите размерность матрицы:\n";
	cin >> n;
	Mtrx matrix(n);
	double a;
	cout << "введите элементы матрицы: \n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a;
			matrix.setValue(i, j, a);
		}
	}
	cout << "Полученная матрица:\n";
	cout << matrix;
	cout << "\nопределитель матрицы: " << matrix.det() << endl;;
	return 0;
}