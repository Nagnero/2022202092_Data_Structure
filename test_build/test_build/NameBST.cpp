#include "NameBST.h"

NameBST::NameBST() : root(nullptr) {
	this->size = 0;
}
NameBST::~NameBST() {

}

NameBSTNode* NameBST::getRoot() {
	return root;
}

// insert
void NameBST::insert(NameBSTNode* newNode) {
	NameBSTNode* curNode = this->getRoot();
	// root가 있으면
	if (curNode) {
		while (1) {
			// curNode가 newNode보다 뒤일때
			if (curNode->getName().compare(newNode->getName()) > 0) {
				// curNode 왼쪽이 있으면 이동
				if (curNode->getLeft()) {
					curNode = curNode->getLeft();
				}
				// curNode 왼쪽이 없으면 삽입
				else {
					newNode->setParent(curNode);
					curNode->setLeft(newNode);
					this->size++;
					break;
				}
			}
			// curNode가 newNode보다 앞일때
			else {
				// curNode 오른쪽이 있으면 이동
				if (curNode->getRight()) {
					curNode = curNode->getRight();
				}
				// curNode 오른쪽이 없으면 삽입
				else {
					newNode->setParent(curNode);
					curNode->setRight(newNode);
					this->size++;
					break;
				}
			}
		}
	}
	// root가 없으면
	else {
		root = newNode;
		this->size++;
	}
}
// search

// print

// delete