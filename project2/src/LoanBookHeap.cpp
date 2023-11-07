#include <stack>
#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
    // exit recursive func. if pN is NULL or pN data is bigger than parrent Node
    if (!pN->getParent())
        return;
    if (pN->getBookData()->getName() > pN->getParent()->getBookData()->getName())
        return;
    
    // swap data if pN data is smaller than parent node data
    if (pN->getBookData()->getName() < pN->getParent()->getBookData()->getName()) {
        LoanBookData* temp = pN->getBookData();
        pN->setBookData(pN->getParent()->getBookData());
        pN->getParent()->setBookData(temp);
        heapifyUp(pN->getParent());
    }
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
    // exit recursive func. if no more child nodes
    if (!pN->getRightChild() && pN->getLeftChild())
        return;

    // if curNode only has left child
    if (!pN->getRightChild()){
        // swap data if parent Node data is bigger
        if (pN->getLeftChild()->getBookData()->getName() < pN->getBookData()->getName()) {
            LoanBookData* temp = pN->getLeftChild()->getBookData();
            pN->getLeftChild()->setBookData(pN->getBookData());
            pN->setBookData(temp);
        }
    }
    else { // if curNode has both left and right child
        // if right child data is smaller than left child data
        if (pN->getRightChild()->getBookData()->getName() < pN->getLeftChild()->getBookData()->getName()) {
            // swap if parent node data is bigger than right node data
            if (pN->getRightChild()->getBookData()->getName() < pN->getBookData()->getName()) {
                LoanBookData* temp = pN->getRightChild()->getBookData();
                pN->getRightChild()->setBookData(pN->getBookData());
                pN->setBookData(temp);
                heapifyDown(pN->getRightChild());
            }
        }
        else { // if left data is smaller than right
            // swap if parent node data is bigger than left node data
            if (pN->getLeftChild()->getBookData()->getName() < pN->getBookData()->getName()) {
                LoanBookData* temp = pN->getLeftChild()->getBookData();
                pN->getLeftChild()->setBookData(pN->getBookData());
                pN->setBookData(temp);
                heapifyDown(pN->getLeftChild());
            }
        }
    }
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

        // insert new Node at last of heap
        if (s.top() == 1) { // 1, set new Node to right
            curNode->setRightChild(newNode);
            newNode->setParent(curNode);
        }
        else if (s.top() == 0) {
            curNode->setLeftChild(newNode);
            newNode->setParent(curNode);
        }

        // rearrange heap
        heapifyUp(newNode);
    }
    else { // if there is no root data
        this->root = newNode;
        this->count++;
    }
    return 0;
}