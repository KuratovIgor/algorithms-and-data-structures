#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

struct Thing {
	double price = 0.0;
	double weight = 0.0;
	double koef = 0.0;
};

void FillArrayOfThings(Thing* arr, const int countThings) {
	for (int i = 0; i < countThings; i++) {
		arr[i].price = 1 + rand() % 49;
		arr[i].weight = 1 + rand() % 9;
		arr[i].koef = arr[i].price / arr[i].weight;
	}
}

void PrintArrayOfThings(Thing* arr, const int countThings) {
	cout << "Prices: ";
	for (int i = 0; i < countThings; i++) {
		cout << arr[i].price << setw(4);
	}
	cout << endl;

	cout << "Weight: ";
	for (int i = 0; i < countThings; i++) {
		cout << arr[i].weight << setw(4);
	}
	cout << endl;

	cout << "-------------------------------------------------------------" << endl;
}

double SearchMax(Thing* things, const int countThings, int* index) {
	double max = 0.0;

	for (int i = 0; i < countThings; i++) {
		if (things[i].koef > max) {
			max = things[i].koef;
			*index = i;
		}
	}

	return max;
}

int TotalSum(Thing* things, const int countThings, int maxWeight) {
	int sum = 0;
	int index = 0;
	double maxKoef = 0.0;

	cout << "Numbers of things: ";
	for (int i = 0; i < countThings; i++) {
		maxKoef = SearchMax(things, countThings, &index);

		if (things[index].weight <= maxWeight) {
			sum += things[index].price;
			maxWeight -= things[index].weight;
			things[index].koef = 0.0;
			cout << index + 1 << setw(4);
		}
		else continue;
	}
	cout << endl;

	return sum;
}

int main() {
	srand((unsigned)time(NULL));
	int maxWeight = 0, countThings = 0;

	cout << "Enter weight bagpack: ";
	cin >> maxWeight;
	cout << "Enter count things: ";
	cin >> countThings;

	cout << "-------------------------------------------------------------" << endl;

	Thing* things = new Thing[countThings];
	FillArrayOfThings(things, countThings);
	PrintArrayOfThings(things, countThings);

	cout << "Sum = " << TotalSum(things, countThings, maxWeight) << endl;

	return 0;
}