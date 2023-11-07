#include <stack>
#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
    LoanBookData* tempData = pN->getBookData();
    pN->setBookData(pN->getParent()->getBookData());
    pN->getParent()->setBookData(tempData);
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {

}

bool LoanBookHeap::Insert(LoanBookData* data) {
    // make new Node
    LoanBookHeapNode* newNode = new LoanBookHeapNode(data);
    if (root) { // if root is occupied
        stack<int> s;

        // calculate heap move stack
        int temp = ++count;
        while(temp != 0) {
            s.push(temp % 2);
            temp /= 2;
        }

        // move to last node of heap (complete tree)
        s.pop();
        LoanBookHeapNode* curNode = root;
        while (s.size() != 1) {
            // if top of stack is 1, move to right
            if (s.top() == 1) 
                curNode = curNode->getRightChild();
            else if (s.top() == 0) // 0, move to left
                curNode = curNode->getLeftChild();
            
            s.pop();
        }

        // insert new Node
        if (s.top() == 1) { // 1, set new Node to right
            curNode->setRightChild(newNode);
            newNode->setParent(curNode);
        }
        else if (s.top() == 0) {
            curNode->setLeftChild(newNode);
            newNode->setParent(curNode);
        }

        // rearrange heap
        while (newNode != root && newNode->getBookData()->getName() < newNode->getParent()->getBookData()->getName()) {
            heapifyUp(newNode);
            newNode = newNode->getParent();
        }
    }
    else { // if there is no root data
        this->root = newNode;
        this->count++;
    }
    return 0;
}