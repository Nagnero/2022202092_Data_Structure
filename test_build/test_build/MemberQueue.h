#pragma once
#include "MemberQueueNode.h"

class MemberQueue
{
private:
	MemberQueueNode* first;
	MemberQueueNode* last;
	int size;

public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	void push(MemberQueueNode* newNode);
	void pop();
	MemberQueueNode* front();
};

