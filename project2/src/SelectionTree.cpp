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
            // find for sibling node
            SelectionTreeNode* sibling;
            if (parent->getLeftChild() == curNode) sibling = parent->getRightChild();
            else sibling = parent->getLeftChild();
            
            //check sibling NULL
            if (sibling->getBookData()) // sibling has data
                if (sibling->getBookData()->getName() < curNode->getBookData()->getName()) 
                    curNode = sibling;

            // check parent is NULL
            if (parent->getBookData()) { // parent is not NULL
                // compare data of curNode and parent Node
                if (curNode->getBookData()->getName() < parent->getBookData()->getName())
                    parent->setBookData(curNode->getBookData());
            }
            else  // if parent is null
                parent->setBookData(curNode->getBookData());
            
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
        
        // move curNode to same data
        if (curNode->getBookData() == left->getBookData()) {
            curNode->setBookData(NULL);
            curNode = left;
        }
        else {
            curNode->setBookData(NULL);
            curNode = right;
        }
    }
    // end of rpeat, curNode become selection tree node that holds run
    LoanBookHeap* runHeap = curNode->getHeap();
    LoanBookHeapNode* rootHeapNode = runHeap->getRoot();

    // get last node
    int count = runHeap->getCount();
    runHeap->decreaseCount();
    stack<int> s;
    while(count != 0) {
        s.push(count % 2);
        count /= 2;
    }

    // move to last node of heap (complete tree)
    s.pop();
    LoanBookHeapNode* lastHeapNode = rootHeapNode;
    while (s.size() != 0) {
        // if top of stack is 1, move to right
        if (s.top() == 1) 
            lastHeapNode = lastHeapNode->getRightChild();
        else if (s.top() == 0) // 0, move to left
            lastHeapNode = lastHeapNode->getLeftChild();
        
        s.pop();
    }

    // move last node data to root node
    // check last node
    if (lastHeapNode != rootHeapNode) { // delete node is not the last node
        // copy last node data to root node
        rootHeapNode->getBookData()->copyBookData(lastHeapNode->getBookData());
        // get last node parent to disconnect
        LoanBookHeapNode* lastHeapNodeParent = lastHeapNode->getParent();
        if (lastHeapNodeParent->getLeftChild() == lastHeapNode)
            lastHeapNodeParent->setLeftChild(NULL);
        else 
            lastHeapNodeParent->setRightChild(NULL);
        // delete last node
        delete lastHeapNode;    
    }
    else { // delete node is the last node
        runHeap->setRoot(NULL);
        delete lastHeapNode;
        rootHeapNode = NULL;
    }

    // heapify down the heap
    if (rootHeapNode) runHeap->heapifyDown(rootHeapNode);    

    // rearrange selection tree
    int codeDivBy100 = runHeap->getCode()/100;
    SelectionTreeNode* curStreeNode = run[codeDivBy100];
    if (runHeap->getRoot())
        curStreeNode->setBookData(runHeap->getRoot()->getBookData());
    SelectionTreeNode* parent = curStreeNode->getParent();

    for (int i = 0; i < 3; i++) {
        // find for sibling node
        SelectionTreeNode* sibling;
        if (parent->getLeftChild() == curStreeNode) sibling = parent->getRightChild();
        else sibling = parent->getLeftChild();

        // curNode and sibling has no data
        if(!curStreeNode->getBookData() && !sibling->getBookData()) {
            curStreeNode = parent;
            parent = curStreeNode->getParent();
            continue;
        }
        else if (!curStreeNode->getBookData()) { // curNode has no data
            parent->setBookData(sibling->getBookData());
            curStreeNode = parent;
            parent = curStreeNode->getParent();
            continue;
        }
        else if (!sibling->getBookData()) { // sibiling has no data
            parent->setBookData(curStreeNode->getBookData());
            curStreeNode = parent;
            parent = curStreeNode->getParent();
            continue;
        }
        else { // both node has data
            if (curStreeNode->getBookData()->getName() > sibling->getBookData()->getName())
                parent->setBookData(sibling->getBookData());
            else
                parent->setBookData(curStreeNode->getBookData());
            curStreeNode = parent;
            parent = curStreeNode->getParent();
            continue;
        }
    }

    return 0;
}


void deleteForPrint(LoanBookHeap* curHeap) {
    // set curHeap and heapNode
    LoanBookHeap* runHeap = curHeap;
    LoanBookHeapNode* rootHeapNode = runHeap->getRoot();

    // get last heap node
    int count = runHeap->getCount();
    runHeap->decreaseCount();
    stack<int> s;
    while(count != 0) {
        s.push(count % 2);
        count /= 2;
    }

    // move to last node of heap (complete tree)
    s.pop();
    LoanBookHeapNode* lastHeapNode = rootHeapNode;
    while (s.size() != 0) {
        // if top of stack is 1, move to right
        if (s.top() == 1) 
            lastHeapNode = lastHeapNode->getRightChild();
        else if (s.top() == 0) // 0, move to left
            lastHeapNode = lastHeapNode->getLeftChild();
        
        s.pop();
    }

    // move last node data to root node
    delete rootHeapNode->getBookData();
    rootHeapNode->setBookData(lastHeapNode->getBookData());
    // delete lastHeapNode and disconnet from heap
    LoanBookHeapNode* tempNode = lastHeapNode->getParent();
    if (tempNode) {
        if (tempNode->getLeftChild() == lastHeapNode)
            tempNode->setLeftChild(NULL);
        else {
            tempNode->setRightChild(NULL);
        }
    }
    delete lastHeapNode;

    runHeap->heapifyDown(rootHeapNode);
}



bool SelectionTree::printBookData(int bookCode) {
    LoanBookHeap* curHeap = this->run[bookCode/100]->getHeap();

    // check run has data
    // if same code has data
    if (curHeap->getRoot()) {
        // copy heap to temp new heap
        LoanBookHeap* tempHeap = new LoanBookHeap(curHeap);

        *fout << "=========PRINT_ST=========" << endl;
         while(1) {
            LoanBookData* outputData = tempHeap->getRoot()->getBookData();
            string _name = outputData->getName();
            int _code = outputData->getCode();
            string _author = outputData->getAuthor();
            int _year = outputData->getYear();
            int _loan_count = outputData->getLoanCount();

            // print data
            *fout << _name << '/';
            if (_code == 0) *fout << "000" << '/';
            else *fout << _code << '/';
            *fout << _author << '/' << _year << '/' << _loan_count << endl;

            if (tempHeap->getCount() != 1)
                deleteForPrint(tempHeap);
            else {
                delete tempHeap;
                break;
            }
        }
        *fout << "=======================" << endl << endl;


        return true;
    }
    else { // if target code don't have data print error
        return false;
    }
}
