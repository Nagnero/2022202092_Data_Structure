#include "Manager.h"

Manager::Manager() {
    
}
Manager::~Manager() {

}

void Manager::run(const char* command) {
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd) {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    // make MemeberQueue, TermsList, NameBST prior to run commands
    MemberQueue* q = new MemberQueue;
    TermsLIST* tl = new TermsLIST;
    NameBST* nb = new NameBST;
    // temporary string variable that gets inputs
    string line;
    while (1) {
        // get one line from command file and save to 'line'
        getline(fcmd, line);

        // check the command and run each process
        if (line == "LOAD")
            LOAD(q);
        else if (line.substr(0, line.find(' ')) == "ADD")
            ADD(q, line);
        else if (line == "QPOP")
            QPOP(tl, q, nb);
        else if (line.substr(0, line.find(' ')) == "SEARCH")
            SEARCH(nb, line);
        else if (line.substr(0, line.find(' ')) == "PRINT")
            PRINT(tl, nb, line);
        else if (line.substr(0, line.find(' ')) == "DELETE")
            DELETE(tl, nb, line);
        else if (line == "EXIT") {
            PrintSuccess("EXIT");
            exit(0);
        }
        else
            exit(1);
    }

    // close input file stream and output file stream
    fcmd.close();
    flog.close();
    return;
}

// function that prints success message
void Manager::PrintSuccess(const char* cmd) {
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}
// function that prints error code
void Manager::PrintErrorCode(int num) {
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;
}

// LOAD
void Manager::LOAD(MemberQueue* q) {
    ifstream fin;
    fin.open("data.txt");

    // error occur when data file doesn't exist
    // or MemeberQueue is empty
    if (!fin.is_open() || !q->empty()) PrintErrorCode(100);
    else {
        string data = "", name, date;
        int age;
        char term;
        // check if data file is opened but, there is no data
        getline(fin, data);
        if (data == "") PrintErrorCode(100);
        else {
            flog << "===== LOAD =====\n";
            // first data input
            stringstream ss(data);
            ss >> name >> age >> date >> term;
            flog << name << '/' << age << '/' << date << '/' << term << '\n';
            MemberQueueNode* newNode = new MemberQueueNode(name, age, date, term);
            q->push(newNode);

            // next data input
            while (1) {
                getline(fin, data);
                // when there's no data, break repeat
                if (data == "")
                    break;
                // store data which is seperated with white space
                stringstream ss(data);
                ss >> name >> age >> date >> term;
                flog << name << '/' << age << '/' << date << '/' << term << '\n';
                MemberQueueNode* newNode = new MemberQueueNode(name, age, date, term);
                q->push(newNode);
            }
            flog << "===============\n\n";
        }
    }
}

// ADD
void Manager::ADD(MemberQueue* q, string line) {
    stringstream ss(line);
    string temp, name, date;
    int age;
    char term;
    ss >> temp >> name >> age >> date >> term;

    if (!(term >= 'A' && term <= 'D') || age > 100) PrintErrorCode(200);
    else {
        MemberQueueNode* newNode = new MemberQueueNode(name, age, date, term);
        flog << "===== ADD =====\n";
        flog << name << '/' << age << '/' << date << '/' << term << '\n';
        flog << "===============\n\n";
        q->push(newNode);
    }
}

// QPOP
void Manager::QPOP(TermsLIST* tl, MemberQueue* q, NameBST* nb) {
    // print error code when queue is empty
    if (q->empty()) PrintErrorCode(300);
    // else pop node and insert to Terms List
    else {
        while (!q->empty()) {
            MemberQueueNode* curMQNode = q->front();
            tl->insert(curMQNode, nb);
            q->pop();
        }
        PrintSuccess("QPOP");
    }
}

// SEARCH
void Manager::SEARCH(NameBST* nb, string line) {
    stringstream ss(line);
    string temp, name;
    ss >> temp >> name;

    NameBSTNode* fn = nb->search(name);
    
    // print error code when no name
    if (!fn) PrintErrorCode(400);
    else {
        flog << "===== SEARCH =====\n";
        flog << name << '/' << fn->getAge() << '/' << fn->getDate() << '/' << fn->getTermDate() << '\n';
        flog << "===============\n\n";
    }
}

// inorder print function with template
// work on both TermsBST and NameBST
template<typename T>
void Manager::inorderPrint(T* curNode) {
    if (curNode == nullptr) return;

    inorderPrint(curNode->getLeft());
    flog << curNode->getName() << '/' << curNode->getAge() << '/' << curNode->getDate() << '/' << curNode->getTermDate() << '\n';
    inorderPrint(curNode->getRight());
}

// PRINT
void Manager::PRINT(TermsLIST* tl, NameBST* nb, string line) {
    stringstream ss(line);
    string temp, input;
    ss >> temp >> input;

    // call print function with TermsBST when input is not "NAME"
    if (input != "NAME") {
        char c = input[0];
        TermsBST* curNode = tl->PRINT(c);

        // print error code when there's no return Node
        if (!curNode) PrintErrorCode(500);
        // else print inorder
        else {
            flog << "===== PRINT =====\n";
            flog << "Terms_BST " << c << '\n';
            inorderPrint(curNode->getRoot());
            flog << "===============\n\n";
        }
    }
    // call print function with NameBST when input is "NAME"
    else {
        // print error code when NameBST is empty
        if(!nb->getRoot()) PrintErrorCode(500);
        // else print inorder
        else {
            flog << "===== PRINT =====\n";
            flog << "Name_BST " << '\n';
            inorderPrint(nb->getRoot());
            flog << "===============\n\n";
        }
    }
}

// DELETE
void Manager::DELETE(TermsLIST* tl, NameBST* nb, string line) {
    // print error code if there is no data
    if (!nb->getRoot()) PrintErrorCode(600);

    stringstream ss(line);
    string temp, input, data;
    ss >> temp >> input >> data;

    // deleting data is about date
    if (input == "DATE") {
        tl->date_delete(nb, data);
    }
    // deleting data is about name
    else {        
        char term = nb->_delete(data);
        // print error code when destinate name doesn't exist
        if(!term) PrintErrorCode(600);
        else {
            tl->name_delete(data, term);
            tl->decrease_size();
        }
    }
    PrintSuccess("DELETE");
}