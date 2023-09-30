#pragma once
#include "MemberQueue.h"
//#include "TermsList.h"
//#include "TermsBST.h"
//#include "NameBST.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Manager
{
private:
	ifstream	fcmd;
	ofstream	flog;

public:
	Manager();
	~Manager();

	void run(const char* command);

	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	// LOAD
	void LOAD(MemberQueue* q);
	// ADD
	void ADD(MemberQueue* q, string line);
	// QPOP
	// SEARCH
	// PRINT
	// DELETE
};
