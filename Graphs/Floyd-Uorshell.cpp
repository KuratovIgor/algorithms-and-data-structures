#include <iostream>
#include <iomanip>

using namespace std;

int** CreateMatrix(const int size); //Creating matrix
int** FloydUorhel(int** matrix, const int size); //Searching the shortest path
void PrintMatrix(int** matrix, const int size); //Printing matrix

const int INFINITI = 1000;

int main() {
	int countTops = 0; //Quantity of tops

	cout << "Enter count tops: ";
	cin >> countTops;

	int** matrix = CreateMatrix(countTops); //Creating adjacency matrix
	PrintMatrix(matrix, countTops); //Printing matrix

	int** floydMatrix = FloydUorhel(matrix, countTops); //Creating matrix with the shortest pathes
	PrintMatrix(floydMatrix, countTops); //Printing matrix

	return 0;
}

int** CreateMatrix(const int size) {
	int distance = 0;

	int** matrix = new int* [size];
	for (int i = 0; i < size; i++)
		matrix[i] = new int[size];

	//Filling all matrix with zeroes
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			matrix[i][j] = 0;

	//Filling adjacency matrix
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i != j && matrix[i][j] == 0) {
				cout << i + 1 << " to " << j + 1 << ": ";
				cin >> distance;
				
				if (distance != -1) //If vertexes connect
					matrix[i][j] = distance;
				else
					matrix[i][j] = INFINITI;

				if (matrix[j][i] == 0)
					matrix[j][i] = matrix[i][j];
			}
		}
	}

	return matrix;
}

int** FloydUorhel(int** matrix, const int size) {
	for (int k = 0; k < size; ++k)
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
					matrix[i][j] = matrix[i][k] + matrix[k][j];
				}
					

	return matrix;
}

void PrintMatrix(int** matrix, const int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (matrix[i][j] != INFINITI)
				cout << setw(4) << matrix[i][j];
			else //If vertexes isn't connect
				cout << setw(4) << '&';
		}
		cout << endl;
	}
	cout << endl;
}