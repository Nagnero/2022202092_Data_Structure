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
	// 큐에 저장된 요소가 있는 경우
	if (first != NULL) {
		this->last->setNext(newNode);
		newNode->setPrev(this->last);
		this->last = newNode;
	} 
	// 큐에 저장된 요소가 없는 경우
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