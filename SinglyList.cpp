#include <iostream>

using namespace std;

struct Node { 
	int value; 
	Node* next; 
};

Node* createNode() { 
	Node* node = new Node;
	node->value = 0;
	node->next = nullptr;
	return node;
}

Node* pushValue(Node* current, const int value) { 
	bool check = false; 
	Node* tValue = createNode(); 
	tValue->value = value;
	Node* temp = createNode();
	temp = current;

	if (current->value > tValue->value) {
		tValue->next = current; 

		current = tValue;      
		temp = tValue;        
	}
	else {
		while (current->next != nullptr) { 
			if (current->next->value < tValue->value) { 
				current = current->next;             
			}
			else {
				tValue->next = current->next;  
				current->next = tValue;       
				check = true;                
				break;                     
			}
		}
		if (check == false) { 
			tValue->next = nullptr;
			current->next = tValue;
		}
	}

	current = temp; 
	return current;
}

Node* deleteValue(Node* current, const int value, bool* check) { 
	Node* temp = createNode(); 
	Node* front = createNode();
	temp = current;
	front = current;

	if (temp->value == value) { 
		if (temp->next == nullptr) {
			*check = false;       
			delete temp;
		}
		else { 
			current = temp->next;
			delete temp;
		}
	}
	else {
		while (temp->next->value != value) temp = temp->next; 
		front = temp->next;
		temp->next = front->next; 
		delete front; 
	}
	
	return current;
}

int searchValue(Node* current, const int value) { 
	Node* temp = createNode();
	temp = current;
	int index = 0; 

	if (temp->value == value) { 
		return 0;            
	}
	else {
		if (temp->next == nullptr) { 
			return -1;
		}
		else { 
			index += 1;
			while (temp->next->value != value) {
				index++;
				temp = temp->next;
				if (temp->next == nullptr) return -1; 
			}
			return index;
		}
	}
}

void printList(Node* current) { 
	Node* temp = createNode(); 
	temp = current;
	cout << "List: ";
	while (temp->next != nullptr) {
		cout << temp->value << "  ";
		temp = temp->next;
	}
	cout << temp->value << endl;
}

void clearList(Node* current) { 
	Node* temp = createNode();
	temp = current;

	while (current->next != nullptr) {
		current = current->next;
		delete temp;
		temp = current;
	}
	delete current;
}

void showMenu() { 
	cout << "Choose: " << endl;
	cout << '\t' << "1) Create List" << endl;
	cout << '\t' << "2) Add element of list" << endl;
	cout << '\t' << "3) Delete element from list" << endl;
	cout << '\t' << "4) Search element in list" << endl;
	cout << '\t' << "5) Show list" << endl;
	cout << '\t' << "6) Finish work with list" << endl;
	cout << '\t' << "7) Clear screen" << endl;
	cout << '\t' << "8) Exit" << endl;
	cout << '\t' << "0) Menu" << endl;
}

int main() {
	setlocale(LC_ALL, "rus");

	const int KEY = 27;

	showMenu();

	int key = 0;
	int value = 0;
	int sizeFile = 0;
	bool listBuilding = false;

	while (1) {
		Node* current = createNode();
		Node* temp = createNode();

		while (1) {
			cout << '\t' << "Enter key: ";
			cin >> key;
			switch (key)
			{
			case 1: {
				if (listBuilding == true) {
					cout << "List already create!" << endl;
				}
				else {
					listBuilding = true;
					cout << "Enter element: ";
					cin >> value;
					current->value = value;
				}
				cout << endl;
			}break;
			case 2: {
				if (listBuilding == false) {
					cout << "List don't create!" << endl;
				}
				else {
					cout << "Enter element: ";
					cin >> value;
					temp = current;
					bool inList = false;

					do {
						if (temp->value == value) {
							inList = true;
							break;
						}
						if (temp->next != nullptr) temp = temp->next;
					} while (temp->next != nullptr);
					if (temp->value == value) inList = true;

					if (inList == true) {
						cout << "Element already in list!" << endl;
					}
					else {
						current = pushValue(current, value);
					}
				}
				cout << endl;
			}break;
			case 3: {
				if (listBuilding == false) {
					cout << "List don't create!" << endl;
				}
				else {
					cout << "Enter element: ";
					cin >> value;
					temp = current;
					bool inList = false;

					do {
						if (temp->value == value) {
							inList = true;
							break;
						}
						if (temp->next != nullptr) temp = temp->next;
					} while (temp->next != nullptr);
					if (temp->value == value) inList = true;

					if (inList == true) {
						current = deleteValue(current, value, &listBuilding);
					}
					else {
						cout << "Element don't search!" << endl;
					}
				}
				cout << endl;
			}break;
			case 4: {
				if (listBuilding == false) {
					cout << "List don't create!" << endl;
				}
				else {
					cout << "Enter element: ";
					cin >> value;

					int index = searchValue(current, value);
					if (index == -1) {
						cout << "Element don't search!" << endl;
					}
					else
					{
						cout << "Index of element: " << index << endl;
					}
				}
				cout << endl;
			}break;
			case 5: {
				if (listBuilding == false)
					cout << "List don't create!" << endl;
				else
					printList(current);
				cout << endl;
			}break;
			case 6: {
				if (listBuilding == false)
					cout << "List don't create!" << endl;
				else {
					clearList(current);
					cout << "List was deleted!" << endl;
					listBuilding = false;
				}
				cout << endl;
			}break;
			case 7: {
				system("cls");
				showMenu();
			}break;
			case 8: {
				delete current;
				delete temp;
				exit(1);
			}break;
			case 0: {
				cout << endl;
				showMenu();
				cout << endl;
			}break;
			default: {
				cout << endl;
			}break;
			}
			if (key == 6 || listBuilding == false) break;
		}
	}

	return 0;
}
