#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {
    // if B+-tree is already occupied
    if(this->root) {
        // find node that has same data
        BpTreeNode* curNode = searchDataNode(newData->getName());

    }
    else { // if B+-tree is empty
        // make new B+-tree Node and set data
        BpTreeDataNode* newNode = new BpTreeDataNode();
        newNode->insertDataMap(newData->getName(), newData);
        this->root = newNode;
    }

	return true;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	
}

BpTreeNode* BpTree::searchDataNode(string name) {
	BpTreeNode* pCur = root;
    // only indexNode has MostLeftChild
    while(pCur->getMostLeftChild()) {
        // current indexnode's map data
        map<string, BpTreeNode*>* curIndexMap = pCur->getIndexMap();

        // if curNode has target name
        if(curIndexMap->find(name) != curIndexMap->end()) {
            pCur = curIndexMap->find(name)->second;
            // get data node that has target name
            while (pCur->getMostLeftChild())
                pCur = pCur->getMostLeftChild();
        }
        else { // if curNode doesn't has taget name
            // save string stored in map
            string first = curIndexMap->begin()->first, second = "";
            if (curIndexMap->size() == 2)
                second = curIndexMap->end()->first;
            
            // move pCur to left
            if (name < first) pCur = pCur->getMostLeftChild();
            else {
                // check second data
                if (second == "") // move to mid node
                    pCur = curIndexMap->begin()->second;
                else {
                    if (name < second)
                        pCur = curIndexMap->begin()->second;
                    else
                        pCur = curIndexMap->end()->second;
                }
            }
        }
    }

    map<string, LoanBookData*>* curDataMap = pCur->getDataMap();

    // if data map has finding name
    if (curDataMap->find(name) != curDataMap->end())
    	return pCur;
    else
        return NULL;
}

bool BpTree::searchBook(string name) {

}

bool BpTree::searchRange(string start, string end) {
	
}
