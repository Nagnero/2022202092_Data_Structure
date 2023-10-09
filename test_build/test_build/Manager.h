#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Manager
{
private:
	ifstream fcmd;
	ofstream flog;

public:
	Manager();
	~Manager();

	void run(const char* command);

	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);
	template<typename T>
	void inorderPrint(T* curNode);

	// LOAD
	void LOAD(MemberQueue* q);
	// ADD
	void ADD(MemberQueue* q);
	// QPOP
	void QPOP(TermsLIST* tl, MemberQueue* q, NameBST* nb);
	// SEARCH
	void SEARCH(NameBST* nb);
	// PRINT
	void PRINT(TermsLIST* tl, NameBST* nb);
	// DELETE
	void DELETE(TermsLIST* tl, NameBST* nb);
};
