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
		// 삽입노드가 기준보다 작은경우
		if (curTBNode->getKey() > newTBNode->getKey()) {
			// 왼쪽 자식이 없는 경우
			if (!curTBNode->getLeft()) {
				curTBNode->setLeft(newTBNode);
				newTBNode->setParent(curTBNode);
				break;
			}
			// 왼쪽 자식이 있는 경우 이동
			else {
				curTBNode = curTBNode->getLeft();
			}
		}
		// 삽입노드가 기준보다 클 경우
		else {
			// 오른쪽 자식이 없는 경우
			if (!curTBNode->getRight()) {
				curTBNode->setRight(newTBNode);
				newTBNode->setParent(curTBNode);
				break;
			}
			// 오른쪽 자식이 있는 경우 이동
			else {
				curTBNode = curTBNode->getRight();
			}
		}
	}
}
// print

// delete