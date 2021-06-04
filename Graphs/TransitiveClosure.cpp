#include <iostream>
#include <iomanip>

using namespace std;

int** CreateMatrix(const int size); 
void PrintMatrix(int** matrix, const int size);
int** TransitiveClosure(int** matrix, const int size);

const int INFINITI = 1000;

int main() {
	int countTops = 0; 

	cout << "Enter count tops: ";
	cin >> countTops;

	int** matrix = CreateMatrix(countTops); 
	PrintMatrix(matrix, countTops); 

	int** transitiveMatrix = TransitiveClosure(matrix, countTops); 

	PrintMatrix(transitiveMatrix, countTops); 

	return 0;
}

int** CreateMatrix(const int size) {
	int distance = 0;

	int** matrix = new int* [size];
	for (int i = 0; i < size; i++)
		matrix[i] = new int[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			matrix[i][j] = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i != j && matrix[i][j] == 0) {
				cout << i + 1 << " to " << j + 1 << ": ";
				cin >> distance;

			    matrix[i][j] = distance;
			}
		}
	}

	return matrix;
}

int** TransitiveClosure(int** matrix, const int size) {
	for (int k = 0; k < size; ++k)
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				if (2 == matrix[i][k] + matrix[k][j]) {
					matrix[i][j] = 1;
				}

	return matrix;
}

void PrintMatrix(int** matrix, const int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (matrix[i][j] != -1)
				cout << setw(4) << matrix[i][j];
			else 
				cout << setw(4) << '0';
		}
		cout << endl;
	}
	cout << endl;
}