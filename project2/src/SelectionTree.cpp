#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) {
    int codeDivBy100 = newData->getCode() / 100;
    this->leafHeap[codeDivBy100]->Insert(newData);
    return 0;
}

bool SelectionTree::Delete() {
return 0;
}

bool SelectionTree::printBookData(int bookCode) {
return 0;
}