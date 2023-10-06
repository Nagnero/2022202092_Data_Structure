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
NameBSTNode* NameBST::search(string name) {
	NameBSTNode* curNode = getRoot();

	while (1) {
		// 찾는 노드가 없는 경우 NULL 반환
		if (!curNode) return curNode;

		int res = name.compare(curNode->getName());
		// 이름이 같은 노드를 찾으면 반환
		if (res == 0) return curNode;
		// 찾는 이름이 curNode의 이름보다 작을 경우
		else if (res < 0) curNode = curNode->getLeft();
		// 찾는 이름이 curNode의 이름보다 클 경우
		else curNode = curNode->getRight();
	}
}

// delete