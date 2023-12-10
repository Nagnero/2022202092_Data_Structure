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

    // set queue
    queue<int> q;
    q.push(vertex);

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

bool DFS(Graph* graph, char option, int vertex, ofstream *fout) {
    // set boolean array to check visit
    bool* visited = new bool[graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++)
        visited[i] = false;
    visited[vertex] = true;

    *fout << "========DFS========\n";
    if (option == 'Y') *fout << "Directed Graph DFS result\n";
    else *fout << "Undirected Graph DFS result\n";
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

    // use stack to DFS
    stack<int> s;
    s.push(vertex);

    while(!s.empty()) {
        vertex = s.top();
        s.pop();

        for (auto iter = tempMap[vertex].begin(); iter != tempMap[vertex].end(); iter++) {
            int next = iter->first;
            // if next vertex is not visted
            if (!visited[next]) {
                visited[next] = true;
                s.push(next);
                *fout << " -> " << next;
                break;
            }
        }
    }
    *fout << "\n====================\n\n";

    delete[] tempMap;
    delete[] visited;
    return true;
}

void insertionSort(vector<pair<int, pair<int, int>>>* arr, int low, int high) {
    int j;
    pair<int, pair<int, int>> tempPair; 
    
    // outer loop
    for (int i = low + 1; i <= high; i++) { 
        tempPair = arr->at(i);
        // inner loop
        for (j = i - 1; j >= low; j--){
            if(arr->at(j).first > tempPair.first) // swap pair
                arr->at(j + 1) = arr->at(j); 
            else
                break;
        }
        arr->at(j+1) = tempPair;
    }
}

int partition(vector<pair<int, pair<int, int>>>* arr, int left, int right) {
    int pivot = arr->at(left).first;
    int temp, low = left, high = right + 1;
    pair<int, pair<int, int>> tempPair; 

    do {
        do low++; while (low <= right && arr->at(low).first < pivot);
        do high--; while (high >= left && arr->at(high).first > pivot);

        // swap two data
        if (low <= high) {
            tempPair=arr->at(low);
            arr->at(low) = arr->at(high);
            arr->at(high) = tempPair;
        }
    } while (low < high);

    tempPair = arr->at(left); // swap step. set pivot
    arr->at(left) = arr->at(high);
    arr->at(high) = tempPair;

    return high;
}

void quickSort(vector<pair<int, pair<int, int>>>* arr, int low, int high) {
    int segmentSize = high - low + 1;

    if (low < high) {
        if (segmentSize <= 6)
            insertionSort(arr, low, high);
        else {
            int pivot = partition(arr, low, high);

            quickSort(arr, low, pivot - 1);
            quickSort(arr, pivot + 1, high);
        }
    }
}

class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);

        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void merge(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v) {
            if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else {
                parent[root_u] = root_v;
                if (rank[root_u] == rank[root_v]) {
                    rank[root_v]++;
                }
            }
        }
    }
};

bool Kruskal(Graph* graph, ofstream *fout) {
    int size = graph->getSize();
    map<int, int>* tempMap = new map<int, int>[size + 1];
    // vector.first == weight, vector.second.first == from, vector.second.second == to
    vector<pair<int, pair<int, int>>> edges;
    // copy undirected graph to temp Map
    for (int i = 1; i <= size; i++) 
        graph->getAdjacentEdges(i, tempMap);
    for (int i = 1; i <= size; i++)
        for (auto iter = tempMap[i].begin(); iter != tempMap[i].end(); iter++) 
            edges.push_back({ iter->second, {i, iter->first} });

    quickSort(&edges, 0, edges.size() - 1);

    DisjointSet ds(size);
    // result mst
    vector<pair<int, pair<int, int>>> r_mst;

    // loop as edge size
    for (auto edge : edges) {
        int weight = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        // if Edge doesn't create a cycle, add it to the MST
        if (set_u != set_v) {
            r_mst.push_back({weight, {u, v}});
            ds.merge(set_u, set_v);
        }
    }

    *fout << "========Kruskal========" << endl;
    for (int i = 0; i <= r_mst.size(); i++) {
        *fout << "[" << i + 1 << "]\t";
        if (i < 9) *fout << "\t";
        for (auto edge : r_mst) {
            if (edge.second.first == i + 1)
                *fout << edge.second.second << "(" << edge.first << ")";
            if (edge.second.second == i + 1)
                *fout << edge.second.first << "(" << edge.first << ")";
        }
        *fout << endl;
    }
    int total = 0;
    for (auto edge : r_mst) total += edge.first;
    *fout << "cost: " << total << endl;
    *fout << "================\n\n";

    delete[] tempMap;
    return true;
}

bool Dijkstra(Graph* graph, char option, int vertex) {

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