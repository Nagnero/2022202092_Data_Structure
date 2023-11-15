#include <string>
#include <algorithm>
#include "Manager.h"
using namespace std;

void Manager::run(const char* command) 
{
	fcmd.open(command);
	if(!fcmd) {
		flog << "File Open Error" << endl;
        fcmd.close();
        delete this->bptree;
        delete this->stree;
		return;
	}
    flog.open("log.txt", ios::app);

    string line;
	while (1) {
		getline(fcmd, line); // get one command line
        // check fcmd is empty
        if (line == "") break;
        // check the command and run each process
        if (line.substr(0, line.find('\t')) == "LOAD") {
            // if no tab is input
            if (line.find('\t') == string::npos) {
                // check correct method of input
                if (line.length() == 4)
                    LOAD();
                else
                    printErrorCode(100);
            }
            else { // if there is tab
                // remove white space
                line.erase(remove_if(line.begin(), line.end(), 
                        [](unsigned char x) { return std::isspace(x); }), line.end());
                
                // check correct method of input
                if (line.length() == 4)
                    LOAD();
                else
                    printErrorCode(100);
            }
        }
        else if (line.substr(0, line.find('\t')) == "ADD")
            ADD(line);
        else if (line.substr(0, line.find('\t')) == "SEARCH_BP") {
            int index = line.find('\t'); // string parsing index
            if (index == -1) { // no data
                printErrorCode(300);
                continue;
            }
            line = line.substr(index + 1);
            index = line.find('\t');
            string first = line.substr(0, index); // get first data
            index = line.find('\t');
            if (index == -1) { // book name input
                SEARCH_BP_BOOK(first);
            }
            else {
                string second = line.substr(index + 1); // get second data
                SEARCH_BP_RANGE(first, second);
            }
        }
        else if (line.substr(0, line.find('\t')) == "PRINT_BP"){
            // if no tab is input
            if (line.find('\t') == string::npos) {
                // check correct method of input
                if (line.length() == 8)
                    PRINT_BP();
                else
                    printErrorCode(400);
            }
            else { // if there is tab
                // remove white space
                line.erase(remove_if(line.begin(), line.end(), 
                        [](unsigned char x) { return std::isspace(x); }), line.end());
                
                // check correct method of input
                if (line.length() == 8)
                    PRINT_BP();
                else
                    printErrorCode(400);
            }
        }
        else if (line.substr(0, line.find('\t')) == "PRINT_ST")
            PRINT_ST(line);
        else if (line == "DELETE")
            DELETE();
        else if (line == "EXIT") {
            printSuccessCode("EXIT");
            fcmd.close();
            flog.close();
            delete this->bptree;
            delete this->stree;
            exit(0);
        }
        else {
            printErrorCode(700);
            // remove line
            line = "";
        }
	}
	fcmd.close();
    flog.close();
    delete this->bptree;
    delete this->stree;
	return;
}

bool Manager::LOAD() {
    ifstream fin;
    string data, name, s_code, author, s_year, s_loan_count;
    int code, year, loan_count;
    fin.open("loan_book.txt");

    // error occur when data file doesn't exist
    // or B+-tree already has data
    if (!fin.is_open() || this->bptree->getRoot()) printErrorCode(100);
    else { // continue loading data
        while (1) {
            if (fin.eof()) break; // break if file is end
            getline(fin, data);
            if (data == "") break; // break if no more loan book data

            int index = data.find('\t'); // string parsing index
            name = data.substr(0, index); // get name
            data = data.substr(index + 1);
            s_code = data.substr(0, index = data.find('\t')); // get code
            data = data.substr(index + 1);
            author = data.substr(0, index = data.find('\t')); // get author
            data = data.substr(index + 1);
            s_year = data.substr(0, index = data.find('\t')); // get year
            data = data.substr(index + 1);
            s_loan_count = data.substr(0, data.find('\t')); // get loan book count

            // change string to integer
            code = stoi(s_code);
            year = stoi(s_year);
            loan_count = stoi(s_loan_count);
            // make new data object that save book info.
            LoanBookData* newData = new LoanBookData;
            newData->setBookData(name, code, author, year, loan_count);
            // insert new data into B+-tree
            bptree->Insert(newData);
        }
        printSuccessCode("LOAD");
    }
	return true;
}

bool Manager::ADD(string line) {
    // find tabs and save to array; check missing data
    int index[4] = { -1, };
	index[0] = line.find('\t');
	if (index[0] == -1) {
        printErrorCode(200);
        return true;
    }
	index[1] = line.find('\t', index[0] + 1);
    if (index[1] == -1 || index[0] + 1 == index[1]) {
        printErrorCode(200);
        return true;
    }
	index[2] = line.find('\t', index[1] + 1);
    if (index[2] == -1 || index[1] + 1 == index[2]) {
        printErrorCode(200);
        return true;
    }
	index[3] = line.find('\t', index[2] + 1);
    if (index[3] == -1 || index[2] + 1 == index[3]) {
        printErrorCode(200);
        return true;
    }
    // check if last input string is tab
    if (line.length() - 1 == index[3]) {
        printErrorCode(200);
        return true;
    }
    // parse with preset index
    string name, author;
    int code, year;
    name = line.substr(index[0] + 1, index[1] - index[0] - 1);
    code = stoi(line.substr(index[1] + 1, index[2] - index[1] - 1));
    author = line.substr(index[2] + 1, index[3] - index[2] - 1);
    year = stoi(line.substr(index[3] + 1));

    // make new object with data
    LoanBookData* newData = new LoanBookData;
    newData->setBookData(name, code, author, year, 0);
    // insert new data into B+-tree
    bptree->Insert(newData);
    flog << "=========ADD=========" << endl;
    flog << name << '/';
    if (code == 0) flog << "000" << '/';
    else flog << code << '/';
    flog << author << '/' << year << endl;
    flog << "=======================" << endl << endl;


	return true;
}

bool Manager::SEARCH_BP_BOOK(string book) {
    bool check = false;
    // check B+ tree empty
    if (this->bptree->getRoot()) 
        check = this->bptree->searchBook(book);

    if (!check)
        printErrorCode(300);

	return true;
}

bool Manager::SEARCH_BP_RANGE(string s, string e) {
    bool check = false;
    // check B+ tree empty
    if (this->bptree->getRoot()) 
        check = this->bptree->searchRange(s, e);

    if (!check)
        printErrorCode(300);

	return true;
}

bool Manager::PRINT_BP() {
    // check stored data in bptree
	if (this->bptree->getRoot()) {
        BpTreeNode* curNode = this->bptree->getRoot();
        while(curNode->getMostLeftChild())
            curNode = curNode->getMostLeftChild();
        
        flog << "=========PRINT_BP=========" << endl;
        while(curNode) {
            map<string, LoanBookData*>* curMap = curNode->getDataMap();
            if (curMap->size() == 0) {
                // move to next data node
                curNode = curNode->getNext();
                continue;
            }
            LoanBookData* curObj = curMap->begin()->second;
            printData(curObj);
            if(curObj != curMap->rbegin()->second) {
                curObj = curMap->rbegin()->second;
                printData(curObj);
            }

            // move to next data node
            curNode = curNode->getNext();
        }
        flog << "=======================" << endl << endl;
    }
    else { // if bptree is empty
        printErrorCode(400);
    }

    return true;
}

bool Manager::PRINT_ST(string line) {
    int code = stoi(line.substr(line.find('\t') + 1));
    bool check = true;
    // check invalid code
    switch(code) {
        case 0: case 100: case 200: case 300: case 400:
        case 500: case 600: case 700: 
            check = this->stree->printBookData(code);
            break;
        default:
            printErrorCode(500);
    }

    // check if stree print is successfull
    // check is false when fail
    if (!check)
        printErrorCode(500);
    
    return true;
}

bool Manager::DELETE() {
    if (this->stree->getRoot()->getBookData()) {
        this->stree->Delete();
        printSuccessCode("DELETE");
    }
    else
        printErrorCode(600);
        
    return true;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "=======================" << endl;
	flog << "ERROR " << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode(const char* cmd) {//SUCCESS CODE PRINT 
    flog << "=========" << cmd << "=========" << endl;
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printData(LoanBookData* curObj) {
    flog << curObj->getName() << '/';
    if (curObj->getCode() == 0) flog << "000" << '/';
    else flog << curObj->getCode() << '/';
    flog << curObj->getAuthor() << '/' << curObj->getYear() << '/' 
        << curObj->getLoanCount() << endl;
}