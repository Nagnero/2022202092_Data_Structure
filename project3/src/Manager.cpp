#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

Manager::Manager() {
	graph = nullptr;	
	fout.open("log.txt");
	load = 0;	//Anything is not loaded
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
      PRINT();
    }

    break;
  }
	cout << "END\n";
	fin.close();
	return;
}

bool Manager::LOAD(const char* filename) {
  // graph by List
	if (strcmp(filename, "graph_L.txt") == 0) {
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
  }
  // graph by Map
  else if (strcmp(filename, "graph_M.txt") == 0) {
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
  }
  // filename is not valid
  else { 
    printErrorCode(100);
    return false;
  }
}

bool Manager::PRINT()	
{

}

bool Manager::mBFS(char option, int vertex)	
{
	
}

bool Manager::mDFS(char option, int vertex)	
{
	
}

bool Manager::mDIJKSTRA(char option, int vertex)	
{
	
}

bool Manager::mKRUSKAL()
{

}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) 
{
	
}

bool Manager::mFLOYD(char option)
{
	
}

bool Manager::mKwoonWoon(int vertex) {
	
}

void Manager::printErrorCode(int n) {
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl << endl;
}


