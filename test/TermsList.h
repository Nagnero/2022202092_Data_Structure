#pragma once
#include "TermsListNode.h"
#include "MemberQueue.h"
#include "NameBST.h"

class TermsLIST {
private:
	TermsListNode* head;
	int size;
	bool delete_success;

public:
	TermsLIST();
	~TermsLIST();

	void setHead(TermsListNode* newTLNode);
	TermsListNode* getHead();
	bool getDelete() { return delete_success; }

	// insert
	void insert(MemberQueueNode* MQNode, NameBST* nb);
	// print
	TermsBST* PRINT(char c);
	// delete
	void name_delete(string name, string target_date, char term);
	void date_delete(NameBST* nb, string termDate);
	void decrease_size() { this->size--; }
};
