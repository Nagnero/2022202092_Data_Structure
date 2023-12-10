#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>

using namespace std;

bool BFS(Graph* graph, char option, int vertex, ofstream *fout) {
    // set queue
    queue<int> q;
    q.push(vertex);
    // set boolean array to check visit
    bool* visited = new bool[graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++)
        visited[i] = false;
    visited[vertex] = true;

    *fout << "========BFS========\n";
    if (option == 'Y') *fout << "Directed Graph BFS result\n";
    else *fout << "Undirected Graph BFS result\n";
    *fout << "startvertex: " << vertex << endl << vertex;

    map<int, int>* tempMap = new map<int, int>[graph->getSize() + 1];
    // with direction
    if (option == 'Y')  {
        // copy directed map to tempMap
        for (int i = 1; i < graph->getSize(); i++) 
            graph->getAdjacentEdgesDirect(i, tempMap);
    }
    // without direction
    else {
        for (int i = 1; i <= graph->getSize(); i++) 
            graph->getAdjacentEdges(i, tempMap);
    }

    // search as BFS
    while (!q.empty()) {
        vertex = q.front();
        q.pop();
        
        for (auto iter = tempMap[vertex].begin(); iter != tempMap[vertex].end(); iter++) {
            int next = iter->first;
            // if next vertex is not visted
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
                *fout << " -> " << next;
            }
        }
    }
    *fout << "\n====================\n\n";
    delete[] tempMap;
    delete[] visited;
    return true;
}

bool DFS(Graph* graph, char option, int vertex)
{
    return true;
}

bool Kruskal(Graph* graph)
{
    return true;
}

bool Dijkstra(Graph* graph, char option, int vertex)
{
    return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex) 
{
    return true;
}

bool FLOYD(Graph* graph, char option)
{
    return true;
}

bool KWANGWOON(Graph* graph, int vertex) {
    return true;
}