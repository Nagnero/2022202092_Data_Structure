#include "Manager.h"
using namespace std;

void Manager::run(const char* command) 
{
	fcmd.open(command);
    flog.open("log.txt");
	if(!fcmd) {
		flog << "File Open Error" << endl;
		return;
	}

    string line;
	while (1) {
		fcmd >> line; // get one command line

        // check the command and run each process
        if (line == "LOAD") 
            LOAD();
        else if (line.substr(0, line.find(' ')) == "ADD")
            ADD();
        else if (line.substr(0, line.find(' ')) == "SEARCH_BP") {

        }
        else if (line == "PRINT_BP")
            PRINT_BP();
        else if (line.substr(0, line.find(' ')) == "PRINT_ST")
            PRINT_ST();
        else if (line == "DELETE")
            DELETE();
        else if (line == "EXIT") {
            cout << "0\n";
            printSuccessCode("EXIT");
            exit(0);
        }
	}
	fcmd.close();
    flog.close();
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
            if (fin.eof()) break; // break if no more loan book data

            getline(fin, data);
            cout << data << endl;

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

            flog << name << endl << s_code << endl;
            flog << author << endl << s_year << endl << s_loan_count<< endl;
        }
    }
	return true;
}

bool Manager::ADD() {
    
	return true;
}

bool Manager::SEARCH_BP_BOOK(string book) 
{
	
}

bool Manager::SEARCH_BP_RANGE(string s, string e) 
{
	
}

bool Manager::PRINT_BP() 
{
	
}

bool Manager::PRINT_ST() 
{

}

bool Manager::DELETE() 
{

}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "=======================" << endl;
	flog << "ERROR " << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode(const char* cmd) {//SUCCESS CODE PRINT 
    flog << "=======" << cmd << "=======" << endl;
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}

