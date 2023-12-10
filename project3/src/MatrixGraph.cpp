#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size) {
    this->m_Mat = new int*[size + 1];
    for (int i = 1; i <= size; ++i) {
        this->m_Mat[i] = new int[size + 1];
        memset(m_Mat[i], 0 , size);
    }
}

MatrixGraph::~MatrixGraph() {
    for (int i = 0; i < this->m_Size; ++i) 
        delete[] this->m_Mat[i]; // delete each row
    
    delete[] this->m_Mat; // delete all
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m) {	
    for (int j = 1; j <= m_Size; j++) {
        if (m_Mat[vertex][j] != 0) {
            pair<int, int> newPair1 = make_pair(j, m_Mat[vertex][j]);
            m[vertex].insert(newPair1);
            pair<int, int> newPair2 = make_pair(vertex, m_Mat[vertex][j]);
            m[j].insert(newPair2);
        }
    }
}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m) {
	for (int j = 1; j <= m_Size; j++) {
        if (m_Mat[vertex][j] != 0) {
            pair<int, int> newPair = make_pair(j, m_Mat[vertex][j]);
            m[vertex].insert(newPair);
        }
    }
}

void MatrixGraph::insertEdge(int from, int to, int weight) {
	this->m_Mat[from][to] = weight;
}

bool MatrixGraph::printGraph(ofstream *fout) {
	*fout << "========== PRINT ==========\n\t\t";
    for (int i = 1; i <= this->m_Size ; i++)
        *fout << "[" << i << "]" << "\t";
    *fout << endl;
    for(int i = 1; i <= this->m_Size; i++) {
        *fout << "[" << i << "]\t";
        if (i < 10) *fout << "\t";
        for (int j = 1; j <= this->m_Size; j++) {
            *fout << this->m_Mat[i][j] << "\t";
            if (j >= 10) *fout << "\t";
        }
        *fout << endl;
    }
    *fout << "==============================\n\n";
    return true;
}
