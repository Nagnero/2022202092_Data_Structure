#ifndef _BpTree_H_
#define _BpTree_H_

#include <queue>
#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include "SelectionTree.h"
#include <fstream>
#include <iostream>

class BpTree {
private:
	BpTreeNode* root;
	int order; // m children
	ofstream* fout;
    SelectionTree* stree;

public:
	BpTree(ofstream *fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree() {
        BpTreeNode* dataNode = root;
        while(dataNode->getMostLeftChild()) 
            dataNode = dataNode->getMostLeftChild();
        BpTreeNode* curNode = root;

        // delete all index nodes
        queue<BpTreeNode*> q;
        while (1) {
            if (!curNode->getMostLeftChild()) break;

            q.push(curNode->getMostLeftChild());
            q.push(curNode->getIndexMap()->begin()->second);
            if (curNode->getIndexMap()->size() == 2) 
                q.push(curNode->getIndexMap()->rbegin()->second);
            
            delete curNode;
            curNode = q.front();
            q.pop();
        }

        // delete all data nodes
        BpTreeNode* delNode;
        while(dataNode->getNext()) {
            delNode = dataNode;
            dataNode = dataNode->getNext();

            delete delNode;
        }
        delete dataNode;
    }

    void setSelectionTree(SelectionTree* stree) { this->stree = stree; }
    /* essential */
	bool		Insert(LoanBookData* newData);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(string name);

	bool searchBook(string name);
	bool searchRange(string start, string end);
    void printData(LoanBookData* curObj);
    void deleteNode(BpTreeNode* curDataNode, string name);
};

#endif
