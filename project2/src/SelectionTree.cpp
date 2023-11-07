#include <queue>
#include <stack>
#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) {
    int codeDivBy100 = newData->getCode() / 100;
    string tempName = "";
    if (run[codeDivBy100]->getHeap()->getRoot())
        tempName = this->run[codeDivBy100]->getHeap()->getRoot()->getBookData()->getName();
    this->run[codeDivBy100]->getHeap()->Insert(newData);

    // rearrange s-tree if root of heap is changed
    if (tempName == "" || tempName != this->run[codeDivBy100]->getHeap()->getRoot()->getBookData()->getName()) {
        SelectionTreeNode* curNode = run[codeDivBy100];
        curNode->setBookData(curNode->getHeap()->getRoot()->getBookData());
        SelectionTreeNode* parent = run[codeDivBy100]->getParent();

        for (int i = 0; i < 3; i++) {
            // check parent is NULL
            if (parent->getBookData()) {
                // compare data of curNode and parent Node
                if (curNode->getBookData()->getName() < parent->getBookData()->getName())
                    parent->setBookData(curNode->getBookData());
            }
            else { // if parent is null
                parent->setBookData(curNode->getBookData());
            }
            curNode = parent;
            parent = curNode->getParent();
        }
    }

    return true;
}

bool SelectionTree::Delete() {
    SelectionTreeNode* curNode = this->root;

    // exit condition: curNode don't have child node
    while(curNode->getLeftChild()) {
        SelectionTreeNode* right = curNode->getRightChild();
        SelectionTreeNode* left = curNode->getLeftChild();
        
        if (curNode->getBookData() == left->getBookData()) {
            curNode->setBookData(NULL);
            curNode = left;
        }
        else {
            curNode->setBookData(NULL);
            curNode = right;
        }
    }
    LoanBookHeap* run = curNode->getHeap();
    LoanBookHeapNode* delHeapNode = run->getRoot();

    return 0;
}

bool SelectionTree::printBookData(int bookCode) {
    LoanBookHeap* curHeap = this->run[bookCode/100]->getHeap();

    // check run has data
    // if same code has data
    if (curHeap->getRoot()) {
        
        return true;
    }
    else { // if target code don't have data print error
        return false;
    }
}

