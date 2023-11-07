#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"

class LoanBookHeap {
private:
    LoanBookHeapNode* root;
    int code;
    int count;

    void deleteHeap(LoanBookHeapNode* curNode) {
        if (curNode) {
            deleteHeap(curNode->getLeftChild());
            deleteHeap(curNode->getRightChild());

            delete curNode;
        }
    }

public:
    LoanBookHeap() {
        this->root = NULL;
    }
    LoanBookHeap(int code) {
        this->root = NULL;
        this->code = code;
        this->count = 0;
    }

    ~LoanBookHeap() {
        deleteHeap(root);
    }
    
    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    void setCode(int code) { this->code = code; }
    LoanBookHeapNode* getRoot() { return root; }

    void heapifyUp(LoanBookHeapNode* pN);
    void heapifyDown(LoanBookHeapNode* pN);
    
    bool Insert(LoanBookData* data);
};
