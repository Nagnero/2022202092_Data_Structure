#include "MemberQueue.h"

MemberQueue::MemberQueue() {
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
	this->max = 100;
}

MemberQueue::~MemberQueue() {

}

// return 1 when Queue is empty, or return 0
bool MemberQueue::empty() {
	if (this->size == 0)
		return 1;
	else
		return 0;
}

// return 1 when Queue is full, or return 0
bool MemberQueue::full() {
	if (this->size == this->max)
		return 1;
	else
		return 0;
}

// MemberQueue push method
void MemberQueue::push(MemberQueueNode* newNode) {
	// end program when Queue is already full
	if (this->full()) exit(1);

	// push when Queue already have Node
	if (first != NULL) {
		this->last->setNext(newNode);
		newNode->setPrev(this->last);
		this->last = newNode;
	} 
	// push when Queue is empty
	else {
		this->first = newNode;
		this->last = newNode;
	}
    // increase number of Nodes
	this->size++;
}

// MemberQueue pop method
void MemberQueue::pop() {
    // end program when Queue is already empty
    if (this->empty()) exit(1);
    // set delete Node
	MemberQueueNode* delMQNode = this->first;

    // pop when Queue has more then 1 node
	if (this->size > 1) {
		this->first = this->first->getNext();
		delete delMQNode;
		this->size--;
	}
    // pop when Queue has only 1 node
	else {
		this->first = NULL;
		this->last = NULL;
		delete delMQNode;
		this->size--;
	}
	
}

// return first Node
MemberQueueNode* MemberQueue::front() {
	return this->first;
}