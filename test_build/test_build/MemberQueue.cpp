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
	if (this->size == 0)
		return 1;
	else
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
void MemberQueue::pop() {
	MemberQueueNode* delMQNode = this->first;

	if (this->size > 1) {
		this->first = this->first->getNext();
		delete delMQNode;
		this->size--;
	}
	else if (this->size == 1) {
		this->first = NULL;
		this->last = NULL;
		delete delMQNode;
		this->size--;
	}
	
}
MemberQueueNode* MemberQueue::front()
{
	return this->first;
}