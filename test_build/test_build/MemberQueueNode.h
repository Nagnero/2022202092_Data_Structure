#pragma once
#include <string>
using namespace std;

class MemberQueueNode {
private:
	MemberQueueNode* next;
	MemberQueueNode* prev;
	string name;
	int age;
	string date;
	char term;

public:
	MemberQueueNode(string name, int age, string date, char term) {
		this->next = NULL;
		this->prev = NULL;
		this->name = name;
		this->age = age;
		this->date = date;
		this->term = term;
	}
	~MemberQueueNode() {

	}

	void setNext(MemberQueueNode* newNode) { this->next = newNode; }
	MemberQueueNode* getNext() { return this->next; }
	void setPrev(MemberQueueNode* newNode) { this->prev = newNode; }
	MemberQueueNode* getPrev() { return this->prev; }
	string getName() { return this->name; }
	int getAge() { return this->age; }
	string getDate() { return this->date; }
	char getTerm() { return this->term; }

};