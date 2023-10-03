#pragma once
#include <string>
using namespace std;
// TermsList�� �� ���; 
// Term, ���� Node, Terms BST�� root ����
class TermsListNode
{
private:
	TermsListNode*	next;
	char term;
	int mem_cnt;

public:
	TermsListNode(char term) {
		this->next = NULL;
		this->term = term;
		this->mem_cnt = 1;
	}
	~TermsListNode() {}

	TermsListNode* getNext() { return next; }
	void setNext(TermsListNode* next) { this->next = next; }
	char getTerm() { return this->term; }
	void setTerm(char t) { this->term = t; }
	int getMem_cnt() { return this->mem_cnt; }
	void increaseMem_cnt() { this->mem_cnt++; }
	void decreaseMem_cnt() { this->mem_cnt--; }
};