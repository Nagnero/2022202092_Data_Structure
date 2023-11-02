#pragma once
#include <string>
using namespace std;

class TermsBSTNode {
private:
	TermsBSTNode* parent;
	TermsBSTNode* left;
	TermsBSTNode* right;
	string name;
	int age;
	string date;
	string termDate;
	int key;

public:
	TermsBSTNode(string name, int age, string date) {
		this->parent = NULL;
		this->left = NULL;
		this->right = NULL;
		this->name = name;
		this->age = age;
		this->date = date;
		this->termDate = "";
		this->key = 0;
	}
	~TermsBSTNode() {}

	TermsBSTNode* getParent() { return this->parent; }
	void setParent(TermsBSTNode* parent) { this->parent = parent; }
	TermsBSTNode* getLeft()	{ return left; }
	void setLeft(TermsBSTNode* left) { this->left = left; }
	TermsBSTNode* getRight() { return right; }
	void setRight(TermsBSTNode* right)	{ this->right = right; }
	string getName() { return this->name; }
	int getAge() { return this->age; }
	string getDate() { return this->date; }
	string getTermDate() { return this->termDate; }
	int getKey() { return this->key; }

	// calculate expire date
	void setTermDate(char term) { 
		size_t yearPos = this->date.find_first_of("-");
		size_t monthPos = this->date.find_last_of("-");

        // get year, month and day as seperate values
		int year = stoi(this->date.substr(0, yearPos));
		int month = stoi(date.substr(yearPos + 1, monthPos - yearPos - 1));
		string day = date.substr(monthPos + 1);

        // add period due to each term
		switch (term) {
		case 'A':
			month += 6;
            // adding month need additional calculation which can over 12
			if (month > 12) {
				year++;
				month -= 12;
			}
			break;
		case 'B':
			year++;
			break;
		case 'C':
			year += 2;
			break;
		case 'D':
			year += 3;
			break;
		}

        // make termDate string after calculation
		string temp = to_string(year) + '-' + (month < 10 ? "0" : "") + 
			to_string(month) + '-'  + day;
		this->termDate = temp;
		this->key = year * 10000 + month * 100 + stoi(day);
	}

};