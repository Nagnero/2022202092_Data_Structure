#pragma once
#include "NameBSTNode.h"

class NameBST {
private:
	NameBSTNode* root;
	int size;

public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();

	// insert
	void insert(NameBSTNode* newNode);
	// search
	// print
	// delete
};