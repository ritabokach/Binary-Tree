#include <iostream>
#include <time.h>
#include <cstdlib>
#include <locale.h>
#include <string>

using namespace std;

struct Node {
	int value;
	Node* left;
	Node* right;
};

Node* BinaryTree(int values[], int& level, int n) {
	if (level >= n) {
		return nullptr;
	}

	Node* newNode = new Node;
	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->value = values[level];

	level++;

	if (newNode->value % 2 != 0) {
		newNode->left = BinaryTree(values, level, n);
	}
	else {
		newNode->right = BinaryTree(values, level, n);
	}
	
	return newNode;
}


void printTree(Node* node, string prefix = "        ") {
	if (node == nullptr) return;

	cout << prefix << node->value << endl;

	string rightPrefix = " ";
	if (node->right != nullptr) {
		cout << prefix << rightPrefix << "\\" << endl;
		printTree(node->right, prefix + "  "); 
	}

	if (node->left != nullptr) {
		string leftPrefix = prefix;
		if (prefix.length() >= rightPrefix.length()) {
			leftPrefix = prefix.substr(0, prefix.length() - rightPrefix.length());
		}
		cout << leftPrefix << "/" << endl;
		printTree(node->left, leftPrefix + "");
	}
}


Node* deleteNodes(Node* node, int nodeValue) {
	if (node == nullptr) {
		return nullptr;
	}

	if (node->value < nodeValue) {
		if (node->left != nullptr) {
			deleteNodes(node->left, nodeValue);
			delete node->left;
			node->left = nullptr;
		}
		if (node->right != nullptr) {
			deleteNodes(node->right, nodeValue);
			delete node->right;
			node->right = nullptr;
		}
		return nullptr;
	}
	// обрабатываем дочерние вершины
	else {
		node->left = deleteNodes(node->left, nodeValue);
		node->right = deleteNodes(node->right, nodeValue);
		return node;
	}
}

void deleteTree(Node* node) {
	if (node == nullptr) {
		return;
	}

	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	int n;
	cout << "Введите количество вершин: ";
	cin >> n;

	if (n < 1) {
		cout << "Введено некорректное значение." << endl;
		return 1;
	}

	int* values = new int[n];
	for (int i = 0; i < n; i++) {
		values[i] = rand() % 100 + 1;
	}

	int level = 0;
	Node* node = BinaryTree(values, level, n);
	cout << "\nИсходное бинарное дерево: " << endl;
	printTree(node);

	if (node != nullptr) {
		int nodeValue = node->value;
		cout << "\nЗначение корня: " << nodeValue << endl;

		node = deleteNodes(node, nodeValue);

		cout << "Бинарное дерево после удаления вершин со значениями меньше " << nodeValue << ":" << endl;
		printTree(node);

		deleteTree(node);

	}

	delete[] values;
	return 0;
}