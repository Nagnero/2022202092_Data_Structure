#include "ListGraph.h"
#include <iostream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size) {
	this->m_List = new map<int, int>[size];
    this->kw_graph = NULL;
}

ListGraph::~ListGraph()	
{
	
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)	 //Definition of getAdjacentEdges(No Direction == Undirected)
{
	
}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
	
}

void ListGraph::insertEdge(int from, int to, int weight) { //Definition of insertEdge
	pair<int, int> newPair = make_pair(to, weight);
    this->m_List[from].insert(newPair);
}

bool ListGraph::printGraph(ofstream *fout) { //Definition of print Graph
	*fout << "========== PRINT ==========\n";
    for(int i = 0; i < this->m_Size; i++) {
        *fout << "[" << i + 1 << "]";
        for (auto it = m_List[i].begin(); it != m_List[i].end(); it++) {
            *fout << " -> (" << it->first << "," << it->second << ")";
        }
        *fout << endl;
    }
    *fout << "==============================\n";
}