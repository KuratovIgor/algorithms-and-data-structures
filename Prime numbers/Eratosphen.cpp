#include <iostream>

using namespace std;


int main()
{
	setlocale(LC_ALL, "ru");

	int N;
	cout << "¬ведите количество чисел в последовательности: " << endl;
	cin >> N;

	int* Arr = new int[N + 1];
	for (int i = 2; i <= N; i++)
	{
		Arr[i] = i;
	}

	for (int i = 2; i <= N / 2; i++)
	{
		for (int j = i * i; j <= N; j += i)
		{
			Arr[j] = 0;
		}
	}

	for (int i = 2; i <= N; i++)
	{
		if (Arr[i] != 0)
			cout << Arr[i] << '\t';
	}

	delete[] Arr;

	return 0;
}
