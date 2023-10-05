#pragma once
#include <string>
using namespace std;

class NameBSTNode {
private:
	NameBSTNode* parent;
	NameBSTNode* left;
	NameBSTNode* right;
	string name;
	int age;
	string date;
	string termDate;
	char term;
	
public:
	NameBSTNode(string name, int age, string date, string termDate, char term) {
		this->parent = NULL;
		this->left = NULL;
		this->right = NULL;
		this->name = name;
		this->age = age;
		this->date = date;
		this->termDate = termDate;
		this->term = term;
	}

	~NameBSTNode() {}

	NameBSTNode* getParent() { return parent; }
	NameBSTNode* getLeft() { return left; }
	NameBSTNode* getRight() { return right; }

	void setParent(NameBSTNode* parent) { this->parent = parent; }
	void setLeft(NameBSTNode* left)	{ this->left = left; }
	void setRight(NameBSTNode* right) { this->right = right; }

	string getName() { return this->name; }
};