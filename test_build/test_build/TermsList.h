#pragma once
#include "TermsListNode.h"
#include "MemberQueue.h"

class TermsLIST
{
private:
	TermsListNode* head;
	int size;

public:
	TermsLIST();
	~TermsLIST();

	void setHead(TermsListNode* newTLNode);
	TermsListNode* getHead();

	// insert
	void insert(MemberQueueNode* MQNode);
	// search
	// delete
};
