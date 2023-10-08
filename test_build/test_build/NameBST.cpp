#include "NameBST.h"

NameBST::NameBST() : root(nullptr) {
	this->size = 0;
}
NameBST::~NameBST() {

}

// return root Node
NameBSTNode* NameBST::getRoot() {
	return root;
}

// insert
void NameBST::insert(NameBSTNode* newNode) {
	NameBSTNode* curNode = this->getRoot();
    
	// when BST root already exist
	if (curNode) {
		while (1) {
			// newNode < curNode
			if (curNode->getName().compare(newNode->getName()) > 0) {
				// move left when curNode has left Node
				if (curNode->getLeft()) curNode = curNode->getLeft();
				// insert Node when left of curNode is empty
				else {
					newNode->setParent(curNode);
					curNode->setLeft(newNode);
					this->size++;
					break;
				}
			}
			// curNode < newNode
			else {
				// move right when curNode has right Node
				if (curNode->getRight()) curNode = curNode->getRight();
				// insert Node when right of curNode is empty
				else {
					newNode->setParent(curNode);
					curNode->setRight(newNode);
					this->size++;
					break;
				}
			}
		}
	}
	// when BST root doesn't exist
	else {
        // make newNode as root Node
		root = newNode;
		this->size++;
	}
}

// search
NameBSTNode* NameBST::search(string name) {
	NameBSTNode* curNode = getRoot();

	while (1) {
		// return NULL when Searching Node is missing
		if (!curNode) return curNode;

		int res = name.compare(curNode->getName());
		// return curNode when it has same name
		if (res == 0) return curNode;
		// move left when finding name is smaller then curNode name
		else if (res < 0) curNode = curNode->getLeft();
		// move right when finding name is larger then curNode name
		else curNode = curNode->getRight();
	}
}

// delete