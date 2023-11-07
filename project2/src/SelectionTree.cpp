#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) {
    int codeDivBy100 = newData->getCode() / 100;
    LoanBookHeapNode* tempNode = this->leafHeap[codeDivBy100]->getRoot();
    this->leafHeap[codeDivBy100]->Insert(newData);
    
    // rearrange s-tree if root of heap is changed
    if (tempNode != this->leafHeap[codeDivBy100]->getRoot())
        reArrange();
}

bool SelectionTree::Delete() {
return 0;
}

bool SelectionTree::printBookData(int bookCode) {
return 0;
}

void SelectionTree::reArrange() {
    
}