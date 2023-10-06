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
        else if (line == "QPOP") {
            QPOP(tl, q, nb);
        }
        else if (line.substr(0, line.find(' ')) == "SEARCH") {
            SEARCH(nb, line);
        }
        else exit(1);
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

    // 텍스트 파일이 존재하지 않거나 큐에 데이터가 들어가 있으면 에러코드 출력
    if (!fin.is_open() || !q->empty()) PrintErrorCode(100);
    else {
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
        flog << "===============\n\n";
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
    // 큐에 노드가 없을 시 에러 코드 출력
    if (q->empty()) PrintErrorCode(300);
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

// PRINT

// DELETE