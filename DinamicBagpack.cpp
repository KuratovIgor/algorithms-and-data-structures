#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

struct Thing {
	int price = 0;
	int weight = 0;
};

void GetInfo(Thing* arr, const int size) {
	cout << endl;
	cout << "Price: ";
	for (int i = 0; i < size; i++)
	{
		cout << setw(4) << arr[i].price;
	}
	cout << endl;

	cout << "Weight:";
	for (int i = 0; i < size; i++)
	{
		cout << setw(4) << arr[i].weight;
	}
	cout << endl;
}

void FillThings(Thing* array, const int size) {
	for (int i = 0; i < size; i++) {
		array[i].price = 1 + rand() % 10;
		array[i].weight = 1 + rand() % 6;

	}
}

int** CreateMatrix(Thing* arrayThings, const int countThings, const int maxWeight) {
	int** matrix = new int* [countThings + 1];
	int temp = 0;

	for (int i = 0; i <= countThings; i++) {
		matrix[i] = new int[maxWeight + 1];
	}

	for (int i = 0; i <= countThings; i++) {
		for (int j = 0; j <= maxWeight; j++) {
			matrix[i][j] = 0;
		}
	}

	for (int i = 1; i <= countThings; i++) {
		for (int j = 0; j <= maxWeight; j++)
		{
			if (arrayThings[i - 1].weight > j && matrix[i - 1][j] == 0)
				continue;
			else {
				if (matrix[i - 1][j] == 0)
					matrix[i][j] = arrayThings[i - 1].price;
				else if (arrayThings[i - 1].weight > j)
					matrix[i][j] = matrix[i - 1][j];
				else {
					temp = matrix[i - 1][(j - arrayThings[i - 1].weight)] + arrayThings[i - 1].price;

					if (temp < matrix[i - 1][j]) {
						matrix[i][j] = matrix[i - 1][j];
					}
					else {
						matrix[i][j] = temp;
					}
				}
			}
		}
	}

	return matrix;
}

void PrintArray(int** matrix, const int countThings, const int maxWeight) {
	cout << endl << "Weight: ";
	for (int i = 0; i <= maxWeight; i++)
	{
		cout << setw(4) << i;
	}

	cout << endl << "-----------------------------------------------------------------------------------------------------" << endl;

	cout << "        ";
	for (int i = 0; i <= maxWeight; i++)
	{
		cout <<  setw(4) << matrix[0][i];
	}

	cout << endl;

	for (int i = 1; i <= countThings; i++) {
		cout << "thing " << i << ":";
		for (int j = 0; j <= maxWeight; j++)
		{
			cout << setw(4) << matrix[i][j];
		}
		cout << endl;
	}

	cout << endl;
}

void PutThings(Thing* things, int** matrix, const int row, const int col) {
	int index = col;

	cout << "Total sum = " << matrix[row][col] << endl;
	cout << "Things in Bagpack: ";
	for (int i = row; i > 0; i--)
	{
		if (matrix[i][index] == matrix[i - 1][index])
			continue;

		cout << "thing" << i << " ";

		index -= things[i - 1].weight;
	}

	cout << endl;
}

int main() {
	srand((unsigned)time(NULL));
	int maxWeight = 0, countThings = 0;
	cout << "Enter weight bagpack: ";
	cin >> maxWeight;
	cout << "Enter count things: ";
	cin >> countThings;

	Thing* arrayThings = new Thing[countThings];
	FillThings(arrayThings, countThings);

	GetInfo(arrayThings, countThings);

	int** matrix = CreateMatrix(arrayThings, countThings, maxWeight);
	PrintArray(matrix, countThings, maxWeight);

	PutThings(arrayThings, matrix, countThings, maxWeight);

	return 0;
}