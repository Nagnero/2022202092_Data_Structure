#ifndef _BpTree_H_
#define _BpTree_H_

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
	~BpTree();

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
