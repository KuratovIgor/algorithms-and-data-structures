#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

class Tree {
private:
	int value = 0;
	Tree* left = nullptr;
	Tree* right = nullptr;

public:
	Tree() { }

	Tree(int value) {
		this->value = value;
	}

	void SetValue(int value) {
		this->value = value;
	}

	Tree* Push(const int value, bool* isPushed) {
		Tree* newList = new Tree(value);
		Tree* temp = this;

		while (1) {
			if (value == temp->value) {
				*isPushed = false;
				return this;
			}
			if (value < temp->value) {
				if (temp->left == nullptr) {
					temp->left = newList;
					*isPushed = true;
					return this;
				}
				temp = temp->left;
			}

			if (value > temp->value) {
				if (temp->right == nullptr) {
					temp->right = newList;
					*isPushed = true;
					return this;
				}
				temp = temp->right;
			}
		}
	}

	Tree* Delete(int value, bool* isDeleted, bool* isTreeExist) {
		Tree* current = this;
		Tree* parent = nullptr;

		while (current != nullptr && current->value != value) {
			parent = current;

			if (value < current->value)
				current = current->left;
			else
				current = current->right;
		}

		if (current == nullptr)
		{
			*isDeleted = false;
			return this;
		}

		if (current->left == nullptr) {
			if (this == current) {
				if (this->right == nullptr) {
					*isTreeExist = false;
					*isDeleted = true;
				}
				else {
					*this = *current->right;
					*isDeleted = true;
				}
				
				return this;
			}

			if (parent != nullptr && parent->left == current)
				parent->left = current->right;
			
			if (parent != nullptr && parent->right == current)
				parent->right = current->right;

			delete current;
			*isDeleted = true;

			return this;
		}

		if (current->right == nullptr) {
			if (this == current) {
				*this = *current->left;
				*isDeleted = true;
				return this;
			}

			if (parent != nullptr && parent->left == current)
				parent->left = current->left;

			if (parent != nullptr && parent->right == current)
				parent->right = current->left;

			delete current;
			*isDeleted = true;

			return this;
		}

		Tree* replace = current->right;

		while (replace->left != nullptr)
			replace = replace->left;

		int replaceValue = replace->value;
		this->Delete(replaceValue, isDeleted, isTreeExist);
		current->value = replaceValue;
	}

	bool SearhList(int value) {
		Tree* current = this;

		while (current != nullptr && current->value != value) {
			if (value < current->value)
				current = current->left;

			if (value > current->value)
				current = current->right;
		}

		if (current == nullptr)
			return false;
		else
			return true;
	}

	void PrintTree(int space = 0) {
		if (this != nullptr) {

			if (this->right != nullptr)
				this->right->PrintTree(space + 4);

			if (space) {
				cout << setw(space) << " ";
			}

			if (this->right != nullptr)
				cout << " /\n" << setw(space) << " ";

			cout << this->value << endl;

			if (this->left != nullptr) {
				cout << setw(space) << " " << " \\\n";
				this->left->PrintTree(space + 4);
			}
		}
	}
};

void ShowMenu() {
	cout << "M E N U:" << endl;
	cout << "  0 - Show menu" << endl;
	cout << "  1 - Create tree" << endl;
	cout << "  2 - Push list" << endl;
	cout << "  3 - Delete list" << endl;
	cout << "  4 - Search list" << endl;
	cout << "  5 - Print tree" << endl;
	cout << "  6 - Exit" << endl;
}

int main() {
	ShowMenu();

	Tree* tree = new Tree();
	int answer = 0, value = 0;
	bool isTreeExist = false, isTreeAlreadyCreated = false;

	while (1) {
		cout << "   Choosen: ";
		cin >> answer;

		switch (answer)
		{
		case 0: {
			cout << endl;
			ShowMenu();
		}break;
		case 1: {
			if (isTreeAlreadyCreated == false) {
				cout << "Enter root value: ";
				cin >> value;

				tree->SetValue(value);

				isTreeExist = true;
				cout << "Tree is created!" << endl;

				isTreeAlreadyCreated = true;
			}
			else
				cout << "Tree is already created!" << endl;
		}break;
		case 2: {
			if (isTreeExist == true) {
				bool isPushed = false; 

				cout << "Enter value: ";
				cin >> value;

				tree->Push(value, &isPushed);

				if (isPushed == true)
					cout << "Value is pushed!" << endl;
				else
					cout << "This value is already exist!" << endl;
			}
			else
				cout << "Tree isn't exist!" << endl;
		}break;
		case 3: {
			if (isTreeExist == true) {
				bool isDeleted = false;

				cout << "Enter value: ";
				cin >> value;

				tree->Delete(value, &isDeleted, &isTreeExist);

				if (isTreeExist == false)
					isTreeAlreadyCreated = false;

				if (isDeleted == true)
					cout << "Value is deleted!" << endl;
				else
					cout << "This value isn't exist!" << endl;
			}
			else
				cout << "Tree isn't exist!" << endl;		
		}break;
		case 4: {
			if (isTreeExist == true) {
				cout << "Enter value: ";
				cin >> value;

				if (tree->SearhList(value) == true)
					cout << "This value is exist in tree!" << endl;
				else
					cout << "This value isn't exist in tree!" << endl;
			}
			else
				cout << "Tree isn't exist!" << endl;		
		}break;
		case 5: {
			if (isTreeExist == true) {
				cout << endl;
				tree->PrintTree();
				cout << endl;
			}
			else
				cout << "Tree isn't exist!" << endl;		
		}break;
		case 6: {
			exit(1);
		}break;
		default:
			break;
		}
	}

	return 0;
}