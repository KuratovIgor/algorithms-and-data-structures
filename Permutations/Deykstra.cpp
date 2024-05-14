#include <iostream>

using namespace std;

void fillArray(int arr[], const int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = i + 1;
	}
}
void printArray(int arr[], const int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << ' ';
	}
}
int fact(int n)
{
	if (n == 1) return 1;
	else return n * fact(n - 1);
}

void deykstra(int arr[], const int size);

int main()
{
	setlocale(LC_ALL, "ru");

	int N = 0;
	cout << "Enter N: ";
	cin >> N;

	int* P = new int[N];

	fillArray(P, N);
	printArray(P, N);
	cout << endl;

	for (int i = 0; i < fact(N) - 1; i++)
	{
		deykstra(P, N);
	}

	delete[] P;

	return 0;
}

void deykstra(int arr[], const int size)
{
	int i = size - 2;
	getchar();
	while (i >= 0)
	{
		if (arr[i] < arr[i + 1])
		{
			break;
		}
		i--;
	}

	int min = i + 1; 
	int j = i + 1;
	for (j; j < size; j++)
	{
		if (arr[i] < arr[j] && arr[j] < arr[min]) min = j;
	}
	int buf = arr[i];
	arr[i] = arr[min];
	arr[min] = buf;

	int k = size - 1;
	j = i + 1;
	while (j < k)
	{
		buf = arr[j];
		arr[j] = arr[k];
		arr[k] = buf;
		j++;
		k--;
	}
	printArray(arr, size);
}
