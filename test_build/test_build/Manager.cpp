#include "Manager.h"

Manager::Manager()
{

}
Manager::~Manager()
{

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
    string line;
    while (1) {
        getline(fcmd, line);

        if (line == "LOAD")
            LOAD();
        else if (line == "ADD")
            break;
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
void Manager::LOAD() {
    ifstream fin;
    fin.open("data.txt");

    MemberQueue q;
    string data = " ", name, date;
    int age;
    char term;
    while (1) {
        getline(fin, data);
        // �Է��� ������ �ݺ��� out
        if (data == "")
            break;
        // �Է°� �������� ������ ����
        stringstream ss(data);
        ss >> name >> age >> date >> term;

        MemberQueueNode* newNode = new MemberQueueNode(name, age, date, term);
        q.push(newNode);
    }
}

// ADD

// QPOP

// SEARCH

// PRINT

// DELETE