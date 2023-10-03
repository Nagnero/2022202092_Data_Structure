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
void TermsLIST::insert(MemberQueueNode* MQNode) {
	string inputName = MQNode->getName();
	int inputAge = MQNode->getAge();
	string inputDate = MQNode->getDate();
	char inputTerm = MQNode->getTerm();
	
	TermsListNode* curTLNode = this->getHead();
	bool addNew = false; // TermsListNode�� ���Ӱ� �߰��ϴ��� Ȯ���ϴ� �÷���

	// ��Ұ� ������ �߰� flag on
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


	// TermsListNode ���Ӱ� ���� �߰�
	if (addNew) {
		TermsListNode* newTLNode = new TermsListNode(inputTerm);

		// TermsBSTNode �� TermsBST ���� �� TermsListNode�� ����
		TermsBSTNode* newTBNode = new TermsBSTNode(inputName, inputAge, inputDate);
		newTBNode->setTermDate(inputTerm);
		TermsBST* TB = new TermsBST(newTBNode);
		newTLNode->setRoot(TB);

		// ����Ʈ�� ����ִ� ���
		if (!this->size) {
			this->setHead(newTLNode);
		}
		else {
			curTLNode = this->getHead();
			for (int i = 1; i < size; i++)
				curTLNode = curTLNode->getNext();
			curTLNode->setNext(newTLNode);
		}
		this->size++;
	}
	// ���� TermsListNode�� �߰�
	else {
		// curTLNode�� �߰�
		curTLNode->increaseMem_cnt();
	}
}
// search

// delete