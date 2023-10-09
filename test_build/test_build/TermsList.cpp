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
	bool addNew = false; // flag that checks for new TermsListNode

	// on the flag when curNode is NULL
	if (!curTLNode) addNew = true;
    // check if same term exist;
	else {
		addNew = true;
		while (curTLNode) {
            // if same term exist, off the flag and break
			if (curTLNode->getTerm() == inputTerm) {
				addNew = false;
				break;
			}
			curTLNode = curTLNode->getNext();
		}
	}

	// new TermsBSTNode and set termDate
	TermsBSTNode* newTBNode = new TermsBSTNode(inputName, inputAge, inputDate);
	newTBNode->setTermDate(inputTerm);
	// new NameBSTNode and insert to NameBST
	NameBSTNode* newNBNode = new NameBSTNode(inputName, inputAge, inputDate, newTBNode->getTermDate(), inputTerm);
	nb->insert(newNBNode);
    
	// check flag and add new TermsListNode
	if (addNew) {
		TermsListNode* newTLNode = new TermsListNode(inputTerm);

		// new TermsBSTNode and TermsBST, connect to TermsListNode
		TermsBST* TB = new TermsBST(newTBNode);
		newTLNode->setRoot(TB);

		// newNode as head when List is empty
		if (!this->size) this->setHead(newTLNode);
        // push newNode at last
		else {
			curTLNode = this->getHead();
			for (int i = 1; i < size; i++)
				curTLNode = curTLNode->getNext();
			curTLNode->setNext(newTLNode);
		}
	}
	// add TermsListNode to existing TermsList
	else {
		curTLNode->increaseMem_cnt();
		curTLNode->getRoot()->insert(newTBNode);
	}
	this->size++;
}

// print
TermsBST* TermsLIST::PRINT(char c) {
	TermsListNode* curNode = getHead();

    // return Node pointer which have same term
	while (curNode) {
		if (curNode->getTerm() == c)
			return curNode->getRoot();
		else
			curNode = curNode->getNext();
	}

    // if there's no same term, return NULL
	return NULL;
}

// delete
void TermsLIST::name_delete(string name, char term) {
	TermsListNode* curTLNode = this->getHead();
	TermsBST* curBST = NULL;

	// get target TermsBST
	while (1) {
		if (curTLNode->getTerm() == term) {
			curBST = curTLNode->getRoot();
			break;
		}
		else
			curTLNode = curTLNode->getNext();
	}

	bool check_empty = curBST->_delete(name);
	// delete TermsList if TermsBST is empty
	if (check_empty) {
		TermsListNode* prevNode = this->getHead();
		while (!(prevNode->getNext() == curTLNode))
			prevNode = prevNode->getNext();
		prevNode->setNext(NULL);
		delete curTLNode;
	}
	this->size--;		
}

void TermsLIST::date_delete(string termDate) {
	TermsListNode* curTLNode = this->getHead();

	while (curTLNode) {
		TermsBST* curBST = curTLNode->getRoot();
		int check_empty = curBST->date_delete(termDate);
		TermsListNode* delNode = curTLNode;
		curTLNode = curTLNode->getNext();

		if (!check_empty) {
			delete curBST;
			TermsListNode* prevNode = this->getHead();
			while (!(prevNode->getNext() == delNode))
				prevNode = prevNode->getNext();
			prevNode->setNext(delNode->getNext());
			delete delNode;
		}

		if (check_empty != 101)
			for (int i = 0; i < check_empty; i++) curTLNode->decreaseMem_cnt();

	}
}