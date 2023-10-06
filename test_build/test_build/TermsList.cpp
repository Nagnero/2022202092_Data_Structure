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

	// TermsBSTNode ����
	TermsBSTNode* newTBNode = new TermsBSTNode(inputName, inputAge, inputDate);
	newTBNode->setTermDate(inputTerm);
	// NameBSTNode ����
	NameBSTNode* newNBNode = new NameBSTNode(inputName, inputAge, inputDate, newTBNode->getTermDate(), inputTerm);
	nb->insert(newNBNode);
	// TermsListNode ���Ӱ� ���� �߰�
	if (addNew) {
		TermsListNode* newTLNode = new TermsListNode(inputTerm);

		// TermsBSTNode �� TermsBST ���� �� TermsListNode�� ����
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
	}
	// ���� TermsListNode�� �߰�
	else {
		// curTLNode�� �߰�
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