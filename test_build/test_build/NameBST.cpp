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
	// root�� ������
	if (curNode) {
		while (1) {
			// curNode�� newNode���� ���϶�
			if (curNode->getName().compare(newNode->getName()) > 0) {
				// curNode ������ ������ �̵�
				if (curNode->getLeft()) {
					curNode = curNode->getLeft();
				}
				// curNode ������ ������ ����
				else {
					newNode->setParent(curNode);
					curNode->setLeft(newNode);
					this->size++;
					break;
				}
			}
			// curNode�� newNode���� ���϶�
			else {
				// curNode �������� ������ �̵�
				if (curNode->getRight()) {
					curNode = curNode->getRight();
				}
				// curNode �������� ������ ����
				else {
					newNode->setParent(curNode);
					curNode->setRight(newNode);
					this->size++;
					break;
				}
			}
		}
	}
	// root�� ������
	else {
		root = newNode;
		this->size++;
	}
}

// search
NameBSTNode* NameBST::search(string name) {
	NameBSTNode* curNode = getRoot();

	while (1) {
		// ã�� ��尡 ���� ��� NULL ��ȯ
		if (!curNode) return curNode;

		int res = name.compare(curNode->getName());
		// �̸��� ���� ��带 ã���� ��ȯ
		if (res == 0) return curNode;
		// ã�� �̸��� curNode�� �̸����� ���� ���
		else if (res < 0) curNode = curNode->getLeft();
		// ã�� �̸��� curNode�� �̸����� Ŭ ���
		else curNode = curNode->getRight();
	}
}

// delete