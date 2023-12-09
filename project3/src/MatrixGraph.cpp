#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size) {
    this->m_Mat = new int*[size];
    for (int i = 0; i < size; ++i) {
        this->m_Mat[i] = new int[size];
        memset(m_Mat[i], 0 , size);
    }
}

MatrixGraph::~MatrixGraph() {
    for (int i = 0; i < this->m_Size; ++i) 
        delete[] this->m_Mat[i]; // delete each row
    
    delete[] this->m_Mat; // delete all
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{	

}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
	
}

void MatrixGraph::insertEdge(int from, int to, int weight) {
	this->m_Mat[from][to] = weight;
}

bool MatrixGraph::printGraph(ofstream *fout) {
	*fout << "========== PRINT ==========\n\t\t";
    for (int i = 1; i < this->m_Size + 1; i ++)
        *fout << "[" << i << "]" << "\t";
    *fout << endl;
    for(int i = 0; i < this->m_Size; i++) {
        *fout << "[" << i + 1 << "]\t";
        if (i + 1 < 10) *fout << "\t";
        for (int j = 0; j < this->m_Size; j++) 
            *fout << this->m_Mat[i][j] << "\t";
        *fout << endl;
    }
    *fout << "==============================\n\n";
    return true;
}
