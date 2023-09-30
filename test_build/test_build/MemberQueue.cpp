#include "MemberQueue.h"

MemberQueue::MemberQueue()
{
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
}
MemberQueue::~MemberQueue()
{

}

bool MemberQueue::empty()
{
	return 0;
}
bool MemberQueue::full()
{
	return 0;
}
void MemberQueue::push(MemberQueueNode* newNode) {
	// ť�� ����� ��Ұ� �ִ� ���
	if (first != NULL) {
		this->last->setNext(newNode);
		newNode->setPrev(this->last);
		this->last = newNode;
	} 
	// ť�� ����� ��Ұ� ���� ���
	else {
		this->first = newNode;
		this->last = newNode;
	}
	this->size++;
}
MemberQueueNode* MemberQueue::pop()
{
	return this->first;
}
MemberQueueNode* MemberQueue::front()
{
	return this->first;
}