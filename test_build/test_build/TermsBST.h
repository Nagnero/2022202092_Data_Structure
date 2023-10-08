#pragma once
#include "TermsBSTNode.h"
#include "MemberQueue.h"

class TermsBST {
private:
	TermsBSTNode* root;

public:
	TermsBST(TermsBSTNode* root);
	~TermsBST();

	TermsBSTNode* getRoot();

	// insert
	void insert(TermsBSTNode* newTBNode);
	// search
	TermsBSTNode* search(string name);
	// delete
	bool _delete(string name);
};