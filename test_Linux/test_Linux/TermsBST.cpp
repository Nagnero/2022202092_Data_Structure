#include <queue>
#include "TermsBST.h"
#include "NameBST.h"

TermsBST::TermsBST(TermsBSTNode* root) {
	this->root = root;
	this->cnt = 0;
	this->size = 0;
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

TermsBSTNode* TermsBST::search(string name) {
	TermsBSTNode* curNode = getRoot();

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

// delete by name; return 1, when empty
bool TermsBST::_delete(string name) {
	TermsBSTNode* destNode = search(name);

	TermsBSTNode* parentNode = destNode->getParent();
	// destNode is leafNode
	if (destNode->getLeft() == NULL && destNode->getRight() == NULL) {
		// no parentNode
		if (!parentNode) this->root = NULL;

		delete destNode;
		delete this;
		return 1;
	}
	// destNode has two child
	else if (destNode->getLeft() && destNode->getRight()) {
		TermsBSTNode* left = destNode->getLeft();
		TermsBSTNode* right = destNode->getRight();
		TermsBSTNode* replaceNode = right;
		// get replaceNode
		while (replaceNode->getLeft())
			replaceNode = replaceNode->getLeft();
		replaceNode->getParent()->setLeft(NULL);

		// replaceNode has right child and not rightNode
		if (replaceNode->getRight() && (replaceNode != right)) {
			replaceNode->getParent()->setLeft(replaceNode->getRight());
			replaceNode->getRight()->setParent(replaceNode->getParent());
		}

		// if delNode is not root Node
		if (parentNode) {
			// set parentNode and replaceNode
			if (parentNode->getLeft() == destNode)
				parentNode->setLeft(replaceNode);
			else
				parentNode->setRight(replaceNode);
			replaceNode->setParent(parentNode);

			replaceNode->setLeft(left);
			left->setParent(replaceNode);
			if (replaceNode != right) {
				replaceNode->setRight(right);
				right->setParent(replaceNode);
			}
		}
		// if delNode is root Node
		else {
			if (replaceNode->getParent()->getLeft() == replaceNode)
				replaceNode->getParent()->setLeft(NULL);

			this->root = replaceNode;
			replaceNode->setParent(NULL);
			replaceNode->setLeft(left);
			left->setParent(replaceNode);
			replaceNode->setRight(right);
			right->setParent(replaceNode);
		}
	}
	// destNode has one child
	else {
		TermsBSTNode* childNode = destNode->getLeft();
		if (!childNode) childNode = destNode->getRight();

		// if destNode is not root Node
		if (parentNode) {
			if (parentNode->getLeft() == destNode)
				parentNode->setLeft(childNode);
			else
				parentNode->setRight(childNode);

			childNode->setParent(parentNode);
		}
		// if destNode is root Node
		else {
			this->root = childNode;
			childNode->setParent(NULL);
		}

		delete destNode;
	}

	return 0;
}

// delete by termDate
TermsBSTNode* TermsBST::postorder_delete(NameBST* nb, TermsBSTNode* curNode, string termDate) {
	// return nullptr if curNode is empty
	if (!curNode) return nullptr;

	TermsBSTNode* left = postorder_delete(nb, curNode->getLeft(), termDate);
	TermsBSTNode* right = postorder_delete(nb, curNode->getRight(), termDate);

	if (curNode->getTermDate() < termDate) {
		if (curNode == this->root)
			this->root = right;

		nb->_delete(curNode->getName());

		delete curNode;
		this->cnt++;
		return nullptr;
	}

	curNode->setLeft(left);
	curNode->setRight(right);

	return curNode;
}

int TermsBST::date_delete(NameBST* nb, string termDate) {
	this->cnt = 0;
	postorder_delete(nb, this->root, termDate);

	
	return this->cnt;
}