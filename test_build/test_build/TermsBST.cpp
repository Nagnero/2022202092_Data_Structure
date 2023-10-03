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
		// ���Գ�尡 ���غ��� �������
		if (curTBNode->getKey() > newTBNode->getKey()) {
			// ���� �ڽ��� ���� ���
			if (!curTBNode->getLeft()) {
				curTBNode->setLeft(newTBNode);
				newTBNode->setParent(curTBNode);
				break;
			}
			// ���� �ڽ��� �ִ� ��� �̵�
			else {
				curTBNode = curTBNode->getLeft();
			}
		}
		// ���Գ�尡 ���غ��� Ŭ ���
		else {
			// ������ �ڽ��� ���� ���
			if (!curTBNode->getRight()) {
				curTBNode->setRight(newTBNode);
				newTBNode->setParent(curTBNode);
				break;
			}
			// ������ �ڽ��� �ִ� ��� �̵�
			else {
				curTBNode = curTBNode->getRight();
			}
		}
	}
}
// print

// delete