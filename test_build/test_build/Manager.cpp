#include "Manager.h"

Manager::Manager() {
    
}
Manager::~Manager() {

}

void Manager::run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    MemberQueue* q = new MemberQueue;
    TermsLIST* tl = new TermsLIST;
    NameBST* nb = new NameBST;
    string line;
    while (1) {
        getline(fcmd, line);

        if (line == "LOAD")
            LOAD(q);
        else if (line.substr(0, line.find(' ')) == "ADD")
            ADD(q, line);
        else if (line == "QPOP")
            QPOP(tl, q, nb);
    }

    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;
}

// LOAD
void Manager::LOAD(MemberQueue* q) {
    ifstream fin;
    fin.open("data.txt");

    // 텍스트 파일이 존재하지 않으면 에러코드 출력
    if (!fin.is_open() || !q->empty()) {
        flog << "===== ERROR =====\n";
        flog << "100\n";
        flog << "===============\n";
        exit(0);
    }

    string data = "", name, date;
    int age;
    char term;
    flog << "===== LOAD =====\n";
    while (1) {
        getline(fin, data);
        // 입력이 없으면 반복문 out
        if (data == "")
            break;
        // 입력값 공백으로 나누어 저장
        stringstream ss(data);
        ss >> name >> age >> date >> term;
        flog << name << '/' << age << '/' << date << '/' << term << '\n';
        MemberQueueNode* newNode = new MemberQueueNode(name, age, date, term);
        q->push(newNode);
    }
    flog << "===============\n";
}

// ADD
void Manager::ADD(MemberQueue* q, string line) {
    stringstream ss(line);
    string temp, name, date;
    int age;
    char term;
    ss >> temp >> name >> age >> date >> term;
    MemberQueueNode* newNode = new MemberQueueNode(name, age, date, term);
    q->push(newNode);

}

// QPOP
void Manager::QPOP(TermsLIST* tl, MemberQueue* q, NameBST* nb) {
    while (!q->empty()) {
        MemberQueueNode* curMQNode = q->front();
        tl->insert(curMQNode, nb);
        q->pop();
    }
}

// SEARCH

// PRINT

// DELETE