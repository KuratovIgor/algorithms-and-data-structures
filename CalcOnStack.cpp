#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Stack {
	char value = '\0';
	double data = 0.1;
	Stack* next = nullptr;
};

double CharToInt(char ch);
char IntToChar(int value);

Stack* CreateStack();
Stack* Push(Stack* current, const char value, bool* check);
Stack* Delete(Stack* current);
char Top(Stack* current);

Stack* Push(Stack* current, const double value, bool* check);
double TopNum(Stack* current);

bool IsCheckCorrect(string infiks, const int size);
string ToPostfiks(string infiks, int* size, double* arr);
double Calculator(string infiks, int size);

int main() {
	Stack* stack = new Stack;
	string infiks;

	cout << "Enter string: " << endl;

	getline(cin, infiks);
	//cout << (int)infiks[0];
	int size = infiks.length();


	if (IsCheckCorrect(infiks, size) == true) cout << Calculator(infiks, size) << endl;
	else cout << "ERROR!!!" << endl;

	return 0;
}

double CharToInt(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A' + 10;
	else
		return ch - '0';
}
char IntToChar(int value)
{
	if (value <= 9)
		return (char)(value + '0');
	else
		return (char)(value + 55);
}

Stack* CreateStack() {
	Stack* stack = new Stack;
	stack->next = nullptr;
	return stack;
}

Stack* Push(Stack* current, const char value, bool* check) {
	Stack* newStack = CreateStack();
	newStack->value = value;
	newStack->next = nullptr;

	if (*check == true) {
		*check = false;
		return newStack;
	}

	if (current->value != '\0') {
		newStack->next = current;
		current = newStack;
		return newStack;
	}
	else {
		current->value = value;
		return current;
	}
}
Stack* Push(Stack* current, const double value, bool* check) {
	Stack* newStack = CreateStack();
	newStack->data = value;
	newStack->next = nullptr;

	if (*check == true) {
		*check = false;
		return newStack;
	}

	if (current->data != 0.1) {
		newStack->next = current;
		current = newStack;
		return newStack;
	}
	else {
		current->data = value;
		return current;
	}
}

Stack* Delete(Stack* current) {
	Stack* temp = CreateStack();
	temp = current;

	current = current->next;
	delete temp;

	return current;
}

char Top(Stack* current) {
	return current->value;
}
double TopNum(Stack* current) {
	return current->data;
}

bool IsCheckCorrect(string infiks, const int size) {
	int open = 0, close = 0;
	bool isNumThere = false;

	for (int i = 0; i < size; i++) {
		if (infiks[i] == '(') open++;
		if (infiks[i] == ')') close++;
		if (infiks[i] == ' ' || infiks[i] == ']' || infiks[i] == '[' || infiks[i] == '}' || infiks[i] == '{') return false;
		if ((infiks[i] >= 42 && infiks[i] <= 47) && (infiks[i + 1] >= 42 && infiks[i + 1] <= 47)) return false;
		if ((int)infiks[i] >= '0' && (int)infiks[i] <= '9') isNumThere = true;
	}

	if (isNumThere == false) return false;
	if (open == close) return true;
	else return false;
}

string ToPostfiks(string infiks, int* size, double* mas) {
	Stack* stack = CreateStack();
	string result;
	int k = 0;
	bool check = false;
	double val = 0.0;
	vector<double> arr(0);

	int i = 0;
	while (infiks[i] != '\0') {
		if (infiks[i] == '0' && infiks[i - 1] == '/') {
			cout << "ERROR" << endl;
			exit(1);
		}

		if (infiks[i] == '*' || infiks[i] == '/' || infiks[i] == '-' || infiks[i] == '+' || infiks[i] == '(' || infiks[i] == ')') {
			if (i != 0) {
				if ((infiks[i - 1] == '(' && i != 0)) {

					result = result + '0';
					arr.push_back(0);
					k++;
				}
			}
			else if (infiks[i] == '-') {
				result = result + '0';
				arr.push_back(0);
				k++;
			}
			
			switch (infiks[i])
			{
			case '+': {
				if (stack != nullptr) {
					while (Top(stack) == '*' || Top(stack) == '/' || Top(stack) == '-' || Top(stack) == '+') {
						result = result + Top(stack);
						k++;
						if (stack->next == nullptr) {
							check = true;
							stack = Delete(stack);
							break;
						}
						stack = Delete(stack);
					}
				}
				else {
					check = true;
				}
				stack = Push(stack, infiks[i], &check);
			} break;
			case '-': {
				if (stack != nullptr) {
					while (Top(stack) == '*' || Top(stack) == '/' || Top(stack) == '-' || Top(stack) == '+') {
						result = result + Top(stack);
						k++;
						if (stack->next == nullptr) {
							check = true;
							stack = Delete(stack);
							break;
						}
						stack = Delete(stack);
					}
				}
				else {
					check = true;
				}
				stack = Push(stack, infiks[i], &check);
			}break;
			case '*': {
				if (stack != nullptr) {
					while (Top(stack) == '*' || Top(stack) == '/') {
						result = result + Top(stack);
						k++;
						if (stack->next == nullptr) {
							check = true;
							stack = Delete(stack);
							break;
						}
						stack = Delete(stack);
					}
				}
				else {
					check = true;
				}
				stack = Push(stack, infiks[i], &check);
			}break;
			case '/': {
				if (stack != nullptr) {
					while (Top(stack) == '*' || Top(stack) == '/') {
						result = result + Top(stack);
						k++;
						if (stack->next == nullptr) {
							check = true;
							stack = Delete(stack);
							break;
						}
						stack = Delete(stack);
					}
				}
				else {
					check = true;
				}
				stack = Push(stack, infiks[i], &check);
			}break;
			case '(': {
				stack = Push(stack, infiks[i], &check);
			}break;
			case ')': {
				while (Top(stack) != '(') {
					result = result + Top(stack);
					k++;
					stack = Delete(stack);
				}
				stack = Delete(stack);
			}break;
			}

			i++;
		}
		else {
			while (infiks[i] != '*' && infiks[i] != '/' && infiks[i] != '-' && infiks[i] != '+' && infiks[i] != '\0' && infiks[i] != '(' && infiks[i] != ')') {
				result = result + infiks[i];
				val += CharToInt(infiks[i]);
				val *= 10;
				i++;
				k++;
			}
			val /= 10;
			arr.push_back(val);
			val = 0.0;
		}
	}

	for (int i = 0; i < arr.size(); i++) {
		mas[i] = arr[i];
	}

	while (stack != nullptr) {
		result = result + Top(stack);
		k++;
		stack = Delete(stack);
	}
	result[k] = '\0';
	*size = k;

	cout << result << endl;

	return result;
}

double Calculator(string infiks, int size) {
	double result = 0.0, resultStack = 0.0;
	Stack* stack = new Stack;
	bool check = false;
	double* arr = new double[100];
	double val = 0.0;
	int k = 0;
	int sizeMas = 0;

	string postfiks = ToPostfiks(infiks, &size, arr);

	for (int i = 0; i <= size; i++) {
		switch (postfiks[i])
		{
		case '+': {
			resultStack = TopNum(stack);
			stack = Delete(stack);
			resultStack += TopNum(stack);
			if (stack->next == nullptr) {
				check = true;
			}
			stack = Delete(stack);
			stack = Push(stack, resultStack, &check);
		}break;
		case '-': {
			resultStack = TopNum(stack);
			stack = Delete(stack);
			resultStack = TopNum(stack) - resultStack;
			if (stack->next == nullptr) {
				check = true;
			}
			stack = Delete(stack);
			stack = Push(stack, resultStack, &check);
		}break;
		case '*': {
			resultStack = TopNum(stack);
			stack = Delete(stack);
			resultStack *= TopNum(stack);
			if (stack->next == nullptr) {
				check = true;
			}
			stack = Delete(stack);
			stack = Push(stack, resultStack, &check);
		}break;
		case '/': {
			resultStack = TopNum(stack);
			stack = Delete(stack);
			resultStack = TopNum(stack) / resultStack;
			if (stack->next == nullptr) {
				check = true;
			}
			stack = Delete(stack);
			stack = Push(stack, resultStack, &check);
		}break;
		default: {
			val *= 10;
			val += CharToInt(postfiks[i]);
			if (val == arr[k]) {
				stack = Push(stack, arr[k], &check);
				val = 0;
				k++;
			}
		}break;
		}
	}

	delete[] arr;

	return stack->data;
}