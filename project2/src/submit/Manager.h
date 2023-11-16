#pragma once
#include <iostream>
#include <fstream>
#include "SelectionTree.h"
#include "BpTree.h"

class Manager {
private:
    ifstream fcmd;
	ofstream flog;
	char* cmd;
	BpTree* bptree;
	SelectionTree* stree;

public:
	Manager(int bpOrder) {
        this->cmd = NULL;
        this->stree = new SelectionTree(&flog);
		this->bptree = new BpTree(&flog, bpOrder);
        this->bptree->setSelectionTree(this->stree);
    }

	~Manager() {
        
    }
	

	void run(const char* command);
	bool LOAD();
	bool ADD(string line);

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST(string line);

	bool DELETE();

	void printErrorCode(int n);
    void printSuccessCode(const char* cmd);

    void printData(LoanBookData* curObj);

};

