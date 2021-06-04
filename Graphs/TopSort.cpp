#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Son; //Son of node
struct Node; //Node of graph

Node* CreateNode(const int key); //Function for creating node of graph
Son* CreateSon(Node* nextNode); //Finction for creating son of node for graph
Node* PushNode(Node* head, const int keyFirst, const int keySecond); //Function for pushing node in graph
Son* PushSon(Son* son, Node* nextNode); //Function for pushing son
void ShowMenu(); //Function for showing menu

struct Son {
	Node* nextNode = nullptr;
	Son* nextSon = nullptr;
};

struct Node {
	int key = 0; //Value of node
	int count = 0; //Count entries
	Node* nextNode = nullptr;
	Son* nextSon = nullptr;
};

Node* CreateNode(const int key) {
	Node* node = new Node();
	node->key = key;
	return node;
}

Son* CreateSon(Node* nextNode) {
	Son* son = new Son();
	son->nextNode = nextNode;
	return son;
}

Node* PushNode(Node* head, const int keyFirst, const int keySecond) {
	//keyFirst - value of parent
	//keySecond - value of son
	Node* current = head;
	Node* firstNode = nullptr; //Node with keyFirst
	Node* secondNode = nullptr; //Node with keySecond

	bool isFirstExist = false; //If firstNode already in graph
	bool isSecondExist = false; //If secondNode already in graph

	do //Serching firstNode and secondNode in graph
	{
		if (current->key == keyFirst) {
			isFirstExist = true;
			firstNode = current;
		}
			
	    if (current->key == keySecond) {
			isSecondExist = true;
			secondNode = current;
		}	

		if (current->nextNode == nullptr)
			break;

		current = current->nextNode;
	} while ((isFirstExist == false || isSecondExist == false) && current->nextNode != nullptr);

	if (current->key == keyFirst) {
		isFirstExist = true;
		firstNode = current;
	}

	if (current->key == keySecond) {
		isSecondExist = true;
		secondNode = current;
	}

	if (isFirstExist && isSecondExist) { //If firstNode and secondNode is exist in graph, secondNode pushing how son of firstNode
		firstNode->nextSon = PushSon(firstNode->nextSon, secondNode);
		secondNode->count++; //Counting entries
	}
	else if (isFirstExist) { //If is exist only firstNode, creating secondNode and pushing how son of firstNode
		secondNode = CreateNode(keySecond);
		firstNode->nextSon = PushSon(firstNode->nextSon, secondNode);
		secondNode->count++; //Counting entries
		current->nextNode = secondNode; //Pushing in list of nodes
	}
	else if (isSecondExist){ //If is exist only secondNode, creating firstNode and pushing secondNode how son of firstNode
		firstNode = CreateNode(keyFirst);
		firstNode->nextSon = PushSon(firstNode->nextSon, secondNode);
		secondNode->count++; //Counting entries
		current->nextNode = firstNode; //Pushing in list of nodes
	}
	else { //If firstNode and secondNode isn't exist in graph, creating it and pushing secondNode how son of firstNode
		firstNode = CreateNode(keyFirst);
		secondNode = CreateNode(keySecond);
		firstNode->nextSon = PushSon(firstNode->nextSon, secondNode);
		secondNode->count++; //Counting entries
		//Pushing in list of nodes
		firstNode->nextNode = secondNode;
		current->nextNode = firstNode;
	}

	return head;
}

Son* PushSon(Son* son, Node* nextNode) {
	Son* head = son;
	Son* currentSon = CreateSon(nextNode); //Creating son

	if (head == nullptr) { //Creating first son
		head = CreateSon(nextNode);
		head->nextSon = nullptr;
	}
	else { //pushing son in list of sons
		while (son->nextSon != nullptr) {
			son = son->nextSon;
		}

		son->nextSon = currentSon;
	}

	return head;
}

Node* SearchZeroCount(Node* head) {
	Node* temp = head;

	 do {
		 if (temp->count == 0)
			 return temp;

		temp = temp->nextNode;
	 } while (temp->count != 0 && temp->nextNode != nullptr);

	 if (temp->count == 0)
		 return temp;

	return nullptr;
}

bool IsAllVisited(Node* head) {
	Node* temp = head;

	while (temp->nextNode != nullptr) {
		//If count of entries -1, this node already visited
		if (temp->count != -1)
			return false;

		temp = temp->nextNode;
	}

	if (temp->count != -1)
		return false;

	return true;
}

Node* DeleteSons(Node* head) {
	Son* temp;

	while (head->nextSon != nullptr) {
		//After deleting reduce count of entries
		if (head->nextSon->nextNode->count != -1 && head->nextSon->nextNode->count != 0)
			head->nextSon->nextNode->count--;

		temp = head->nextSon;
		head->nextSon = head->nextSon->nextSon;
		delete temp;

		if (head->nextSon == nullptr)
			break;
	}

	return head;
}

void TopSort(Node* head) {
	Node* current = head;
	bool isVisited = false;

	while (true) {
		current = head;

		if (IsAllVisited(current) == false) {
			if ((current = SearchZeroCount(current)) != nullptr) {
				current = DeleteSons(current);
				current->count = -1; //Is visited
				cout << current->key << ' ';
			}
			else {
				cout << "Cyrcle!";
				break;
			}
		}
		else {
			break;
		}
	}
}

void ShowMenu() {
	cout << "MENU" << endl;
	cout << " 1 - Create" << endl;
	cout << " 2 - Push" << endl;
	cout << " 3 - Sort" << endl;
	cout << " 4 - Print" << endl;
	cout << " 5 - Exit" << endl;
}

void Print(Node* node) {
	Node* current = node;

	while (current->nextNode != nullptr) {
		cout << current->key << ' ';
		current = current->nextNode;
	}
	cout << current->key << ' ';

	cout << endl;
}

int main() {
	ShowMenu();

	int answer = 0;
	int key1 = 0, key2 = 0;

	Node* graph = new Node;

	while (1) {
		cout << "  Answer - ";
		cin >> answer;

		switch (answer) {
		case 1: {
			cout << "Enter head - ";
			cin >> key1;

			graph = CreateNode(key1);
		}break;
		case 2: {
			cout << "Enter head - ";
			cin >> key1;
			cout << "Enter son - ";
			cin >> key2;

			graph = PushNode(graph, key1, key2);
		}break;
		case 3: {
			TopSort(graph);
			cout << endl;
		}break;
		case 4: {
			Print(graph);
		}break;
		case 5: {
			exit(1);
		}break;
		}
	}

	return 0;
}
