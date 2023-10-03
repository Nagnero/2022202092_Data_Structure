#pragma once
#include <string>
#include "TermsBST.h"
using namespace std;
// TermsList에 들어갈 노드; 
// Term, 다음 Node, Terms BST의 root 저장
class TermsListNode
{
private:
	TermsListNode*	next;
	char term;
	int mem_cnt;
	TermsBST* TermsRoot;

public:
	TermsListNode(char term) {
		this->next = NULL;
		this->term = term;
		this->mem_cnt = 1;
		this->TermsRoot = NULL;
	}
	~TermsListNode() {}

	TermsListNode* getNext() { return next; }
	void setNext(TermsListNode* next) { this->next = next; }
	char getTerm() { return this->term; }
	void setTerm(char t) { this->term = t; }
	int getMem_cnt() { return this->mem_cnt; }
	void increaseMem_cnt() { this->mem_cnt++; }
	void decreaseMem_cnt() { this->mem_cnt--; }
	TermsBST* getRoot() { return this->TermsRoot; }
	void setRoot(TermsBST* root) { this->TermsRoot = root; }
};