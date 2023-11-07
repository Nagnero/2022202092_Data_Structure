#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) {
    int codeDivBy100 = newData->getCode() / 100;
    LoanBookHeapNode* tempNode = this->run[codeDivBy100]->getHeap()->getRoot();
    this->run[codeDivBy100]->getHeap()->Insert(newData);
    
    // rearrange s-tree if root of heap is changed
    if (tempNode != this->run[codeDivBy100]->getHeap()->getRoot())
        reArrange();
    return true;
}

bool SelectionTree::Delete() {
return 0;
}

bool SelectionTree::printBookData(int bookCode) {
return 0;
}

void SelectionTree::reArrange() {
    
}