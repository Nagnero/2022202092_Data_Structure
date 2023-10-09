#pragma once
#include "TermsListNode.h"
#include "MemberQueue.h"
#include "NameBST.h"

class TermsLIST {
private:
	TermsListNode* head;
	int size;

public:
	TermsLIST();
	~TermsLIST();

	void setHead(TermsListNode* newTLNode);
	TermsListNode* getHead();

	// insert
	void insert(MemberQueueNode* MQNode, NameBST* nb);
	// print
	TermsBST* PRINT(char c);
	// delete
	void name_delete(string name, char term);
	void date_delete(NameBST* nb, string termDate);
	void decrease_size() { this->size--; }
};
