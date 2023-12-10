#include "ListGraph.h"
#include <iostream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size) {
	this->m_List = new map<int, int>[size + 1];
    this->kw_graph = NULL;
}

ListGraph::~ListGraph()	{
	delete[] m_List;
    this->m_List = nullptr;
}

//Definition of getAdjacentEdges(No Direction == Undirected)
void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m) { 
	for (auto it = m_List[vertex].begin(); it != m_List[vertex].end(); it++) {
        // Create a pair representing the edge and insert it into the map
        pair<int, int> newPair1 = make_pair(it->first, it->second);
        m[vertex].insert(newPair1);
        pair<int, int> newPair2 = make_pair(vertex, it->second);
        m[it->first].insert(newPair2);
    }
}

//Definition of getAdjacentEdges(Directed graph)
void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m) {
	for (auto it = m_List[vertex].begin(); it != m_List[vertex].end(); it++) {
        pair<int, int> newPair = make_pair(it->first, it->second);
        m[vertex].insert(newPair);
    }
}

//Definition of insertEdge
void ListGraph::insertEdge(int from, int to, int weight) { 
	pair<int, int> newPair = make_pair(to, weight);
    this->m_List[from].insert(newPair);
}

//Definition of print Graph
bool ListGraph::printGraph(ofstream *fout) { 
	*fout << "========== PRINT ==========\n";
    for(int i = 1; i <= this->m_Size; i++) {
        *fout << "[" << i << "]";
        for (auto it = m_List[i].begin(); it != m_List[i].end(); it++) {
            *fout << " -> (" << it->first << "," << it->second << ")";
        }
        *fout << endl;
    }
    *fout << "==============================\n\n";
    return true;
}