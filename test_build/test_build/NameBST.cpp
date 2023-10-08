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
char NameBST::_delete(string name) {
	NameBSTNode* destNode = search(name);

	// return 0 if target doesn't exist
	if (!destNode) return 0;
	else {
		char term = destNode->getTerm();
		NameBSTNode* parentNode = destNode->getParent();
		// destNode is leafNode
		if (destNode->getLeft() == NULL && destNode->getRight() == NULL) {
			// no parentNode
			if (!parentNode) this->root = NULL;
		}		
		// destNode has two child
		else if (destNode->getLeft() && destNode->getRight()) {
			NameBSTNode* left = destNode->getLeft();
			NameBSTNode* right = destNode->getRight();
			NameBSTNode* replaceNode = right;
			// get replaceNode
			while (replaceNode->getLeft()) 
				replaceNode = replaceNode->getLeft();
			
			// replaceNode has right child
			if (replaceNode->getRight()) {
				replaceNode->getParent()->setLeft(replaceNode->getRight());
				replaceNode->getRight()->setParent(replaceNode->getParent());
			}

			if (parentNode->getLeft() == destNode)
				parentNode->setLeft(replaceNode);
			else 
				parentNode->setRight(replaceNode);

			replaceNode->setParent(parentNode);
			if (replaceNode != left) {
				replaceNode->setLeft(left);
				left->setParent(replaceNode);
			}
			if (replaceNode != right) {
				replaceNode->setRight(right);
				right->setParent(replaceNode);
			}
		}
		// destNode has one child
		else {
			NameBSTNode* childNode = destNode->getLeft();
			if (!childNode) childNode = destNode->getRight();

			if (parentNode->getLeft() == destNode)
				parentNode->setLeft(childNode);
			else
				parentNode->setRight(childNode);
		}

		delete destNode;
		this->size--;

		return term;
	}
}