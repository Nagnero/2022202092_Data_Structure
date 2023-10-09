#pragma once
#include "TermsBSTNode.h"
#include "MemberQueue.h"
#include "NameBST.h"

class TermsBST {
private:
	TermsBSTNode* root;
	int cnt;

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
	TermsBSTNode* postorder_delete(NameBST* nb, TermsBSTNode* curNode, string termDate);
	int date_delete(NameBST* nb, string termDate);
};