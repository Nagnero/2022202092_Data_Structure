#pragma once
#include "SelectionTreeNode.h"
#include "LoanBookHeap.h"

#include <fstream>
#include <iostream>

class SelectionTree {
private:
    SelectionTreeNode* root;
    ofstream* fout;
    SelectionTreeNode* run[8];

    // make two child node and connect to parent node
    void createChild(SelectionTreeNode* curNode) {
        SelectionTreeNode* left = new SelectionTreeNode;
        SelectionTreeNode* right = new SelectionTreeNode;
        
        curNode->setLeftChild(left);
        curNode->setRightChild(right);
        left->setParent(curNode);
        right->setParent(curNode);
    }

    // create loan book heap and connect to leaf node
    void setLoanBookHeap(SelectionTreeNode* curNode, int index, int code) {
        // make new Heap and connect to leaf node
        LoanBookHeap* newHeap = new LoanBookHeap(code);
        run[index]->setHeap(newHeap);
    }

    // recursively delete tree func.
    void deleteTree(SelectionTreeNode* curNode) {
        if (curNode) {
            deleteTree(curNode->getLeftChild());
            deleteTree(curNode->getRightChild());

            if (curNode->getHeap()) delete curNode->getHeap();
            delete curNode;
        }
    }

public:
    SelectionTree(ofstream* fout) {
        this->fout = fout;
        for (int i = 0; i < 8 ; i++)
            run[i] = new SelectionTreeNode;

        SelectionTreeNode* newNode = new SelectionTreeNode;
        root = newNode;

        // create basic set of tree (level 3)
        createChild(root);
        createChild(root->getLeftChild());
        createChild(root->getRightChild());
        createChild(root->getLeftChild()->getLeftChild());
        createChild(root->getLeftChild()->getRightChild());
        createChild(root->getRightChild()->getLeftChild());
        createChild(root->getRightChild()->getRightChild());

        // set leaf node loan book heap
        setLoanBookHeap(root->getLeftChild()->getLeftChild()->getLeftChild(), 0, 0);
        setLoanBookHeap(root->getLeftChild()->getLeftChild()->getRightChild(), 1, 100);
        setLoanBookHeap(root->getLeftChild()->getRightChild()->getLeftChild(), 2,  200);
        setLoanBookHeap(root->getLeftChild()->getRightChild()->getRightChild(), 3, 300);
        setLoanBookHeap(root->getRightChild()->getLeftChild()->getLeftChild(), 4, 400);
        setLoanBookHeap(root->getRightChild()->getLeftChild()->getRightChild(), 5, 500);
        setLoanBookHeap(root->getRightChild()->getRightChild()->getLeftChild(), 6, 600);
        setLoanBookHeap(root->getRightChild()->getRightChild()->getRightChild(), 7, 700);
    }

    ~SelectionTree() {
        deleteTree(root);
    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    bool Insert(LoanBookData* newData);
    bool Delete();
    bool printBookData(int bookCode);
    void reArrange();
};