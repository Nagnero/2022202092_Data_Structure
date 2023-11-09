#pragma once
#include <queue>
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
    // constructor for copying heap
    LoanBookHeap(LoanBookHeap* curHeap) {
        this->code = 0;
        this->count = 0;

        // copy other nodes
        LoanBookHeapNode* originalNode = curHeap->getRoot();
        queue<LoanBookHeapNode*> q;
        q.push(originalNode);

        while(!q.empty()) {
            LoanBookHeapNode* curHeapNode = q.front();
            q.pop();

            // copy data
            LoanBookData* originalData = curHeapNode->getBookData();
            string _name = originalData->getName();
            int _code = originalData->getCode();
            string _author = originalData->getAuthor();
            int _year = originalData->getYear();
            int _loan_count = originalData->getLoanCount();
            LoanBookData* copyData = new LoanBookData;
            copyData->setBookData(_name, _code, _author, _year, _loan_count);

            this->Insert(copyData);

            if (curHeapNode->getLeftChild()) {
                q.push(curHeapNode->getLeftChild());
            }
            if (curHeapNode->getRightChild()) {
                q.push(curHeapNode->getRightChild());
            }
        }
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
    void setCount(int count) { this->count = count; }
    int getCode() { return this->code; }
    int getCount() { return this->count; }
    void decreaseCount() { this->count--; }
    LoanBookHeapNode* getRoot() { return root; }

    void heapifyUp(LoanBookHeapNode* pN);
    void heapifyDown(LoanBookHeapNode* pN);
    
    bool Insert(LoanBookData* data);
};
