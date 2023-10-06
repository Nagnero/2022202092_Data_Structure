#include "MemberQueue.h"

MemberQueue::MemberQueue()
{
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
	this->max = 100;
}
MemberQueue::~MemberQueue()
{

}

bool MemberQueue::empty() {
	if (this->size == 0)
		return 1;
	else
		return 0;
}
// 가득 차있으면 1 반환
bool MemberQueue::full()
{
	if (this->size == this->max)
		return 1;
	else
		return 0;
}
void MemberQueue::push(MemberQueueNode* newNode) {
	// 큐가 가득 차있는데 push 하는 경우 종료
	if (this->full())
		exit(1);

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
	// 큐가 비어있는데 pop 하는 경우 종료
	else {
		exit(1);
	}
	
}
MemberQueueNode* MemberQueue::front()
{
	return this->first;
}