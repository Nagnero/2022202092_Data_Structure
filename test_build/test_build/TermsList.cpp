#include "TermsList.h"


TermsLIST::TermsLIST(): head(nullptr) {
	this->size = 0;
}
TermsLIST::~TermsLIST() {

}

void TermsLIST::setHead(TermsListNode* newTLNode) {
	this->head = newTLNode;
}
TermsListNode* TermsLIST::getHead() {
	return head;
}

// insert
void TermsLIST::insert(MemberQueueNode* MQNode, NameBST* nb) {
	string inputName = MQNode->getName();
	int inputAge = MQNode->getAge();
	string inputDate = MQNode->getDate();
	char inputTerm = MQNode->getTerm();
	
	TermsListNode* curTLNode = this->getHead();
	bool addNew = false; // TermsListNode를 새롭게 추가하는지 확인하는 플래그

	// 요소가 없으면 추가 flag on
	if (!curTLNode)
		addNew = true;
	else {
		addNew = true;
		while (curTLNode) {
			if (curTLNode->getTerm() == inputTerm) {
				addNew = false;
				break;
			}
			curTLNode = curTLNode->getNext();
		}
	}

	// TermsBSTNode 생성
	TermsBSTNode* newTBNode = new TermsBSTNode(inputName, inputAge, inputDate);
	newTBNode->setTermDate(inputTerm);
	// NameBSTNode 생성
	NameBSTNode* newNBNode = new NameBSTNode(inputName, inputAge, inputDate, newTBNode->getTermDate(), inputTerm);
	nb->insert(newNBNode);
	// TermsListNode 새롭게 만들어서 추가
	if (addNew) {
		TermsListNode* newTLNode = new TermsListNode(inputTerm);

		// TermsBSTNode 및 TermsBST 생성 및 TermsListNode와 연결
		TermsBST* TB = new TermsBST(newTBNode);
		newTLNode->setRoot(TB);

		// 리스트가 비어있는 경우
		if (!this->size) {
			this->setHead(newTLNode);
		}
		else {
			curTLNode = this->getHead();
			for (int i = 1; i < size; i++)
				curTLNode = curTLNode->getNext();
			curTLNode->setNext(newTLNode);
		}
	}
	// 기존 TermsListNode에 추가
	else {
		// curTLNode에 추가
		curTLNode->increaseMem_cnt();
		curTLNode->getRoot()->insert(newTBNode);
	}
	this->size++;
}

// print
TermsBST* TermsLIST::PRINT(char c) {
	TermsListNode* curNode = getHead();

	while (curNode) {
		if (curNode->getTerm() == c)
			return curNode->getRoot();
		else
			curNode = curNode->getNext();
	}

	return NULL;
}

// delete