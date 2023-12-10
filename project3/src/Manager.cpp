#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

Manager::Manager() {
	graph = nullptr;	
	fout.open("log.txt");
	load = 0;	// Anything is not loaded
}

Manager::~Manager() {
	if(load)	//if graph is loaded, delete graph
		delete graph;	
	if(fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char* command_txt) {
	ifstream fin;	//Command File Input File Stream
	fin.open(command_txt, ios_base::in);//File open with read mode
		
	if(!fin) { //If command File cannot be read, Print error
		fout<<"command file open error"<<endl;
		return;	//Return
	}

    string line;
    while (1) {
        // check end of command file
        if (fin.eof()) break;
        getline(fin, line);
        if (line == "") break;
        
        if (line.substr(0, line.find(' ')) == "LOAD") {
            string filename = line.substr(line.find(' ') + 1);
            // error state for no inputs
            if (filename == "LOAD" || filename == " ") {
                printErrorCode(100);
                continue;
            }
            LOAD(filename.c_str());
        }
        else if (line == "PRINT") {
            if (!this->graph) {
                printErrorCode(200);
                continue;
            }
            PRINT();
        }
        else if (line.substr(0, line.find(' ')) == "BFS") {
            // if no graph, error
            if (!this->graph) {
                printErrorCode(300);
                continue;
            }
            string data = line.substr(line.find(' ') + 1);;
            istringstream iss(data);
            vector<string> tokens;
            // split data and save to vector
            string token;
            while (iss >> token) tokens.push_back(token);

            // if input data is not 2, print error code
            if (tokens.size() != 2) {
                printErrorCode(300);
                continue;
            }

            // if direction is not entered, print error
            if (!(tokens[0] == "Y" || tokens[0] == "N")) {
                printErrorCode(300);
                continue;
            }
            // if start vertex is bigger than size
            if (stoi(tokens[1]) > this->graph->getSize()) {
                printErrorCode(300);
                continue;
            }

            mBFS(tokens[0][0], stoi(tokens[1]));
        }
        else if (line.substr(0, line.find(' ')) == "DFS") {
            // if no graph, error
            if (!this->graph) {
                printErrorCode(400);
                continue;
            }
            string data = line.substr(line.find(' ') + 1);;
            istringstream iss(data);
            vector<string> tokens;
            // split data and save to vector
            string token;
            while (iss >> token) tokens.push_back(token);

            // if input data is not 2, print error code
            if (tokens.size() != 2) {
                printErrorCode(300);
                continue;
            }

            // if direction is not entered, print error
            if (!(tokens[0] == "Y" || tokens[0] == "N")) {
                printErrorCode(300);
                continue;
            }
            // if start vertex is bigger than size
            if (stoi(tokens[1]) > this->graph->getSize()) {
                printErrorCode(300);
                continue;
            }

            mDFS(tokens[0][0], stoi(tokens[1]));
        }
        else if (line.substr(0, line.find(' ')) == "KRUSKAL") {
            mKRUSKAL();
        }
        else if (line == "EXIT") {
            break;
        }
    }
	cout << "END\n";
	fin.close();
    fout.close();
	return;
}

bool Manager::LOAD(const char* filename) {
    // graph by List
	if (strcmp(filename, "graph_L.txt") == 0) {
        if (this->graph) delete this->graph;

        ifstream graphData;
        graphData.open(filename);
        // check if data is open
        if (!graphData) {
            cout << "gL\n";
            printErrorCode(100);
            return false;
        }
        // check if file is empty
        graphData.seekg(0, ios::end);
        if (graphData.tellg() == 0) {
            printErrorCode(100);
            return false;
        }

        // parse data and make graph
        graphData.close();
        graphData.open(filename);
        string data;
        getline(graphData, data); // get rid of first data
        getline(graphData, data); // get number of data
        this->graph = new ListGraph(0, stoi(data));
        
        int start = 0;
        while (getline(graphData, data)) {
            istringstream iss(data);
            vector<string> tokens;
            // split data and save to vector
            string token;
            while (iss >> token) tokens.push_back(token);

            if (tokens.size() == 1) {
                start = stoi(tokens[0]);
                continue;
            }

            if (tokens.size() == 2) {
                this->graph->insertEdge(start, stoi(tokens[0]), stoi(tokens[1]));
            }         
        }

        fout << "========LOAD=======" << endl;
        fout << "Success" << endl;
        fout << "====================" << endl << endl;
    }
    // graph by Map
    else if (strcmp(filename, "graph_M.txt") == 0) {
        if (this->graph) delete this->graph;

        ifstream graphData;
        graphData.open(filename);
        // check if data is open
        if (!graphData) {
            printErrorCode(100);
            return false;
        }
        // check if file is empty
        graphData.seekg(0, ios::end);
        if (graphData.tellg() == 0) {
            printErrorCode(100);
            return false;
        }

        // parse data and make graph
        graphData.close();
        graphData.open(filename);
        string data;
        getline(graphData, data); // get rid of first data
        getline(graphData, data); // get number of data
        int num = stoi(data), start = 1;
        this->graph = new MatrixGraph(1, num);

        while (getline(graphData, data)) {
            istringstream iss(data);
            vector<string> tokens;
            tokens.push_back("a");
            // split data and save to vector
            string token;
            while (iss >> token) tokens.push_back(token);

            for (int i = 1; i <= num; i++) {
                this->graph->insertEdge(start, i, stoi(tokens[i]));
            }
            start++;
        }
        fout << "========LOAD=======" << endl;
        fout << "Success" << endl;
        fout << "====================" << endl << endl;
    }
    // filename is not valid
    else { 
        printErrorCode(100);
        return false;
    }
}

bool Manager::PRINT() {
    this->graph->printGraph(&fout);
    return true;
}

bool Manager::mBFS(char option, int vertex)	{
    // if vertex doesn't exist in graph
    if (this->graph->getSize() < vertex) {
        printErrorCode(300);
        return false;
    }

    BFS(this->graph, option, vertex, &fout);
    return true;
}

bool Manager::mDFS(char option, int vertex)	{
    // if vertex doesn't exist in graph
    if (this->graph->getSize() < vertex) {
        printErrorCode(400);
        return false;
    }

    DFS(this->graph, option, vertex, &fout);
    return true;
}

bool Manager::mDIJKSTRA(char option, int vertex)	
{
    return true;
}

bool Manager::mKRUSKAL() {
    Kruskal(this->graph, &fout);
    return true;
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) 
{
    return true;
}

bool Manager::mFLOYD(char option)
{
    return true;
}

bool Manager::mKwoonWoon(int vertex) {
    return true;
}

void Manager::printErrorCode(int n) {
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl << endl;
}

