#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {
    string name = newData->getName();
    // if B+-tree is already occupied
    if (this->root) {
        // find node that has same data
        BpTreeNode* curNode = searchDataNode(name);

        map<string, LoanBookData*>* curDataMap = curNode->getDataMap();

        // insert as new Node
        if (curDataMap->find(name) == curDataMap->end()) {
            // add data into current data node
            curNode->insertDataMap(name, newData);

            // check current data node is full
            if (excessDataNode(curNode)) {
                // split data Node
                splitDataNode(curNode);
            }
        }
        else { // increase loan_book number
            LoanBookData* curobj = curNode->getDataMap()->find(name)->second;
            curobj->updateCount();

            // check possible loan book
            int limit = 0;
            switch (curobj->getCode()) {
            case 0: case 100: case 200:
                limit = 3;
                break;
            case 300: case 400:
                limit = 4;
                break;
            case 500: case 600: case 700:
                limit = 2;
                break;
            default:
                break;
            }
            // move to Loan book heap =========================================
            if (curobj->getLoanCount() == limit) {
                cout << "MOVE\n";
            }
        }
    }
    else { // if B+-tree is empty
        // make new B+-tree Node and set data
        BpTreeDataNode* newNode = new BpTreeDataNode();
        newNode->insertDataMap(name, newData);
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
    // get data map to change data
    map<string, LoanBookData*>* curDataMap = pDataNode->getDataMap();

    // make new Node and set as next node; delete moved data
    BpTreeNode* nextDataNode = new BpTreeDataNode;
    string delName = curDataMap->rbegin()->first;
    nextDataNode->insertDataMap(delName, curDataMap->rbegin()->second);
    pDataNode->deleteMap(delName);
    delName = curDataMap->rbegin()->first;
    nextDataNode->insertDataMap(delName, curDataMap->rbegin()->second);
    pDataNode->deleteMap(delName);

    // if curNode has next node before split, link it
    if (pDataNode->getNext()) {
        nextDataNode->setNext(pDataNode->getNext());
        pDataNode->getNext()->setPrev(nextDataNode);
    }

    // doubly link data node
    pDataNode->setNext(nextDataNode);
    nextDataNode->setPrev(pDataNode);

    // check parent node (index node)
    if (pDataNode->getParent() != NULL) {
        // get index node and set data
        BpTreeNode* curIndexNode = pDataNode->getParent();

        curIndexNode->insertIndexMap(nextDataNode->getDataMap()->begin()->first, nextDataNode);
        pDataNode->getNext()->setParent(curIndexNode);
        // check current index node is full
        if (excessIndexNode(curIndexNode)) {
            splitIndexNode(curIndexNode);
        }
    }
    else { // no parent (no index node)
        // make index node and set data
        BpTreeIndexNode* newIndexNode = new BpTreeIndexNode;
        newIndexNode->insertIndexMap(nextDataNode->getDataMap()->begin()->first, nextDataNode);

        // connect index node with data node
        newIndexNode->setMostLeftChild(pDataNode);
        pDataNode->setParent(newIndexNode);
        pDataNode->getNext()->setParent(newIndexNode);

        // set root
        this->root = newIndexNode;
    }

}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
    // make parent and next index node
    BpTreeNode* parentIndexNode;
    if (pIndexNode->getParent())
        parentIndexNode = pIndexNode->getParent();
    else
        parentIndexNode = new BpTreeIndexNode;
    BpTreeNode* nextIndexNode = new BpTreeIndexNode;
    // find child nodes
    BpTreeNode* lastChildNode = pIndexNode->getIndexMap()->rbegin()->second;

    // copy pIndexNode last obj to nextIndexNode and delete
    string delName = pIndexNode->getIndexMap()->rbegin()->first;
    nextIndexNode->insertIndexMap(delName, pIndexNode->getIndexMap()->rbegin()->second);
    pIndexNode->deleteMap(delName);
    // copy pIndexNode last obj to parentIndexNode and delete
    BpTreeNode* thirdChildNode = pIndexNode->getIndexMap()->rbegin()->second;
    delName = pIndexNode->getIndexMap()->rbegin()->first;
    parentIndexNode->insertIndexMap(delName, pIndexNode->getIndexMap()->rbegin()->second);
    pIndexNode->deleteMap(delName);

    
    // link parent node and pIndexNode
    if (!parentIndexNode->getMostLeftChild())
        parentIndexNode->setMostLeftChild(pIndexNode);
    pIndexNode->setParent(parentIndexNode);
    // link parent node and nextIndexNode
    map <string, BpTreeNode*>* tempMap = parentIndexNode->getIndexMap();
    nextIndexNode->setMostLeftChild(tempMap->find(delName)->second);
    tempMap->find(delName)->second = nextIndexNode;
    nextIndexNode->setParent(parentIndexNode);
    thirdChildNode->setParent(nextIndexNode);
    lastChildNode->setParent(nextIndexNode);
    

    if (this->root == pIndexNode)
        this->root = parentIndexNode;

    if (excessIndexNode(parentIndexNode))
        splitIndexNode(parentIndexNode);
}

BpTreeNode* BpTree::searchDataNode(string name) {
    BpTreeNode* pCur = root;
    // only indexNode has MostLeftChild
    while (pCur->getMostLeftChild()) {
        // current indexnode's map data
        map<string, BpTreeNode*>* curIndexMap = pCur->getIndexMap();

        // if curNode has target name
        if (curIndexMap->find(name) != curIndexMap->end()) {
            pCur = curIndexMap->find(name)->second;
            // get data node that has target name
            while (pCur->getMostLeftChild())
                pCur = pCur->getMostLeftChild();
        }
        else { // if curNode doesn't has taget name
            // save string stored in map
            string first = curIndexMap->begin()->first, second = "";
            if (curIndexMap->size() == 2)
                second = curIndexMap->rbegin()->first;

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
                        pCur = curIndexMap->rbegin()->second;
                }
            }
        }
    }


    return pCur;
}


bool BpTree::searchBook(string name) {
    map<string, LoanBookData*>* curMap = searchDataNode(name)->getDataMap();

    // B+ tree has target data
    if (curMap->find(name) != curMap->end()) {
        LoanBookData* curObj = curMap->find(name)->second;
        
        *fout << "=========SEARCH_BP=========" << endl;
        printData(curObj);
        *fout << "=======================" << endl << endl;

        return true;
    }
    else { // B+ tree donsen't have target data
        return false;
    }
}

bool BpTree::searchRange(string start, string end) {
    BpTreeNode* curNode = searchDataNode(start);
    map<string, LoanBookData*>* curMap = curNode->getDataMap();
    
    // save first and second string to cur data map string
    string first, second = "";
    first = curMap->begin()->first;
    if (first != curMap->rbegin()->first)
        second = curMap->rbegin()->first.substr(0, 1);
    first = curMap->begin()->first.substr(0, 1);
    
    if (second == "") {
        if (first >= start) {
            LoanBookData* curObj = curMap->begin()->second;
            *fout << "=========SEARCH_BP=========" << endl;
            printData(curObj);
        }
    }
    else {
        if (first < start && second > end) return false; // no data in range
        else if (first < start && second < end) {
            LoanBookData* curObj = curMap->rbegin()->second;
            *fout << "=========SEARCH_BP========="<< endl;
            printData(curObj);
        }
        else if (first >= start) {
            LoanBookData* curObj = curMap->begin()->second;
            *fout << "=========SEARCH_BP========="<< endl;
            printData(curObj);
            curObj = curMap->rbegin()->second;
            printData(curObj);
        }
    }
    curNode = curNode->getNext(); // move to next Node

    while (curNode) {
        curMap = curNode->getDataMap();
        first = curMap->begin()->first;
        if (first != curMap->rbegin()->first)
            second = curMap->rbegin()->first.substr(0, 1);
        first = curMap->begin()->first.substr(0, 1);

        // print data and escape rpeat syntax 
        if (second != "") {
            if (second <= end) { // print first, second data
                LoanBookData* curObj = curMap->begin()->second;
                printData(curObj);
                curObj = curMap->rbegin()->second;
                printData(curObj);
            }
            else if (first <= end) { // print first data and end
                LoanBookData* curObj = curMap->begin()->second;
                printData(curObj);
                break;
            }
            else if (first > end) { // don't print any data
                break;
            }
        }
        else {
            if (first <= end) { // print first data
                LoanBookData* curObj = curMap->begin()->second;
                printData(curObj);
            }
            else break;
        }
        curNode = curNode->getNext();
        first = "";
        second = "";
    }
    
    *fout << "=======================" << endl << endl;

	return true;
}

void BpTree::printData(LoanBookData* curObj) {
    *fout << curObj->getName() << '/';
    if (curObj->getCode() == 0) *fout << "000" << '/';
    else *fout << curObj->getCode() << '/';
    *fout << curObj->getAuthor() << '/' << curObj->getYear() << '/' 
        << curObj->getLoanCount() << endl;
}