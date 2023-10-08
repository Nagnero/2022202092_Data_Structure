#include "TermsBST.h"

TermsBST::TermsBST(TermsBSTNode* root) {
	this->root = root;
}

TermsBST::~TermsBST() {

}

TermsBSTNode* TermsBST::getRoot() {
	return root;
}

// insert
void TermsBST::insert(TermsBSTNode* newTBNode) {
	TermsBSTNode* curTBNode = this->getRoot();
	
	while (1) {
		// newNode < curNode
		if (curTBNode->getKey() > newTBNode->getKey()) {
			// move left when curNode has left Node
			if (curTBNode->getLeft()) curTBNode = curTBNode->getLeft();
            // insert Node when left of curNode is empty
            else {
				curTBNode->setLeft(newTBNode);
				newTBNode->setParent(curTBNode);
				break;
			}
		}
		// curNode < newNode
		else {
			// move right when curNode has right Node
			if (curTBNode->getRight()) curTBNode = curTBNode->getRight();
            // insert Node when right of curNode is empty
            else {
				curTBNode->setRight(newTBNode);
				newTBNode->setParent(curTBNode);
				break;
			}
		}
	}
}

// delete