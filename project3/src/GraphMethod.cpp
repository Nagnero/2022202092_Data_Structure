#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>

#define INF 99999999
#define MIN(a,b) a<b ? a:b

using namespace std;

bool BFS(Graph* graph, char option, int vertex, ofstream* fout) {
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
    if (option == 'Y') {
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

bool DFS(Graph* graph, char option, int vertex, ofstream* fout) {
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
    if (option == 'Y') {
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

    while (!s.empty()) {
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
        for (j = i - 1; j >= low; j--) {
            if (arr->at(j).first > tempPair.first) // swap pair
                arr->at(j + 1) = arr->at(j);
            else
                break;
        }
        arr->at(j + 1) = tempPair;
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
            tempPair = arr->at(low);
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
            }
            else {
                parent[root_u] = root_v;
                if (rank[root_u] == rank[root_v]) {
                    rank[root_v]++;
                }
            }
        }
    }
};

bool Kruskal(Graph* graph, ofstream* fout) {
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
            r_mst.push_back({ weight, {u, v} });
            ds.merge(set_u, set_v);
        }
    }

    if (r_mst.size() != size - 1) {
        delete[] tempMap;
        return false;
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

bool Dijkstra(Graph* graph, char option, int vertex, ofstream* fout) {
    int size = graph->getSize();
    map<int, int>* tempMap = new map<int, int>[size + 1];
    // with direction
    if (option == 'Y') {
        // copy directed map to tempMap
        for (int i = 1; i < size; i++)
            graph->getAdjacentEdgesDirect(i, tempMap);
    }
    // without direction
    else {
        for (int i = 1; i <= size; i++)
            graph->getAdjacentEdges(i, tempMap);
    }

    bool check = true;
    // check unvaild weight (minus)
    for (int i = 1; i <= size; i++)
        for (auto iter = tempMap[i].begin(); iter != tempMap[i].end(); iter++)
            if (iter->second < 0) {
                check = false;
                break;
            }
    if (!check) {
        delete[] tempMap;
        return false;
    }

    bool visited[100001]; // check visted array
    int dist[100001]; // shortest path array
    int prev[100001];
    for (int i = 0; i < 100001; i++) { dist[i] = INF; visited[i] = false; prev[i] = -1; }
    dist[vertex] = 0;
    visited[vertex] = true;
    prev[vertex] = 0;

    // shortest path table initialize
    for (auto iter = tempMap[vertex].begin(); iter != tempMap[vertex].end(); iter++) {
        int adjindex = iter->first;
        int weight = iter->second;
        dist[adjindex] = weight;
        prev[adjindex] = vertex;
    }

    // Dijkstra's Algorithm
    for (int i = 1; i < size; i++) {
        int now = 0, minDist = INF;
        for (int j = 1; j <= size; j++) {
            if (dist[j] < minDist && !visited[j]) {
                minDist = dist[j];
                now = j;
            }
        }
        visited[now] = true;

        for (auto iter = tempMap[now].begin(); iter != tempMap[now].end(); iter++) {
            int cost = dist[now] + iter->second;
            if (cost < dist[iter->first]) {
                dist[iter->first] = cost;
                prev[iter->first] = now;
            }
        }
    }

    *fout << "========Dijkstra========" << endl;
    if (option == 'Y') *fout << "Directed Graph Dijkstra result\n";
    else *fout << "Undirected Graph Dijkstra result\n";
    *fout << "startvertex: " << vertex << endl;
    for (int i = 1; i <= size; ++i) {
        if (i == vertex) continue;
        *fout << "[" << i << "]\t";
        if (i <= 9) *fout << "\t";
        if (dist[i] == INF) {
            *fout << "x\n";
            continue;
        }

        // logic that prints from vertex to target
        int index = prev[i];
        stack<int> s;
        s.push(i);
        while (prev[index] != 0) {
            s.push(prev[index]);
            index = prev[index];
        }
        // print stack data
        if (s.top() == vertex) s.pop();
        *fout << vertex;
        while (!s.empty()) {
            *fout << "->" << s.top();
            s.pop();
        }
        *fout << " (" << dist[i] << ")\n";
    }
    *fout << "====================\n\n";

    delete[] tempMap;
    return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream* fout) {
    int size = graph->getSize();
    map<int, int>* tempMap = new map<int, int>[size + 1];
    // with direction
    if (option == 'Y') {
        // copy directed map to tempMap
        for (int i = 1; i < size; i++)
            graph->getAdjacentEdgesDirect(i, tempMap);
    }
    // without direction
    else {
        for (int i = 1; i <= size; i++)
            graph->getAdjacentEdges(i, tempMap);
    }

    bool visited[100001]; // check visted array
    int dist[100001]; // shortest path array
    int prev[100001];
    for (int i = 0; i < 100001; i++) { dist[i] = INF; visited[i] = false; prev[i] = -1; }
    dist[s_vertex] = 0;
    visited[s_vertex] = true;
    prev[s_vertex] = 0;

    // shortest path table initialize
    for (auto iter = tempMap[s_vertex].begin(); iter != tempMap[s_vertex].end(); iter++) {
        int adjindex = iter->first;
        int weight = iter->second;
        dist[adjindex] = weight;
        prev[adjindex] = s_vertex;
    }

    // bellmanford algorithm
    for (int i = 1; i < size; ++i) {
        for (int j = 1; j <= size; ++j) {
            for (auto iter = tempMap[j].begin(); iter != tempMap[j].end(); ++iter) {
                int from = j;
                int to = iter->first;
                int weight = iter->second;

                if (dist[from] != INF && dist[from] + weight < dist[to]) {
                    dist[to] = dist[from] + weight;
                    prev[to] = from;
                    visited[to] = true;
                }
            }
        }
    }

    // check minus cycle
    for (int j = 1; j <= size; ++j) {
        for (auto iter = tempMap[j].begin(); iter != tempMap[j].end(); ++iter) {
            int from = j;
            int to = iter->first;
            int weight = iter->second;

            if (dist[from] != INF && dist[from] + weight < dist[to]) {
                // minus cycle exist
                delete[] tempMap;
                return false;
            }
        }
    }

    *fout << "========Bellman-Ford========" << endl;
    if (option == 'Y') *fout << "Directed Graph Bellman-Ford result\n";
    else *fout << "Undirected Graph Bellman-Ford result\n";
    // logic that prints from vertex to target
    if (dist[e_vertex] > INF - 100) {
        *fout << "x\n";
    }
    else {
        int index = prev[e_vertex];
        stack<int> s;
        s.push(e_vertex);
        while (prev[index] != 0) {
            s.push(prev[index]);
            index = prev[index];
        }
        // print stack data
        if (s.top() == s_vertex) s.pop();
        *fout << s_vertex;
        while (!s.empty()) {
            *fout << "->" << s.top();
            s.pop();
        }
        *fout << "\ncost: " << dist[e_vertex] << endl;
    }
    *fout << "====================\n\n";

    delete[] tempMap;
    return true;
}

bool FLOYD(Graph* graph, char option, ofstream* fout) {
    int size = graph->getSize();
    map<int, int>* tempMap = new map<int, int>[size + 1];
    // with direction
    if (option == 'Y') {
        // copy directed map to tempMap
        for (int i = 1; i < size; i++)
            graph->getAdjacentEdgesDirect(i, tempMap);
    }
    // without direction
    else {
        for (int i = 1; i <= size; i++)
            graph->getAdjacentEdges(i, tempMap);
    }

    int** arr = new int* [size + 1];
    for (int i = 1; i <= size; i++)
        arr[i] = new int[size + 1];

    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++) {
            if (i == j) arr[i][j] = 0;
            else arr[i][j] = INF;
        }

    for (int i = 1; i <= size; i++)
        for (auto iter = tempMap[i].begin(); iter != tempMap[i].end(); iter++) {
            // i: from, iter.first: to, iter.second: weight
            arr[i][iter->first] = iter->second;
        }

    for (int k = 1; k <= size; k++) {
        for (int i = 1; i <= size; i++)
            for (int j = 1; j <= size; j++)
                if (arr[i][k] != INF && arr[k][j] != INF)
                    arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);
    }

    for (int i = 1; i <= size; i++) {
        if (arr[i][i] < 0) {
            delete[] tempMap;
            return false;
        }
    }

    *fout << "========FLOYD========" << endl;
    if (option == 'Y') *fout << "Directed Graph FLOYD result\n\t\t";
    else *fout << "Undirected Graph FLOYD result\n\t\t";
    for (int i = 1; i <= size; i++)
        *fout << "[" << i << "]" << "\t";
    *fout << endl;
    for (int i = 1; i <= size; ++i) {
        *fout << "[" << i << "]\t";
        if (i <= 9) *fout << "\t";
        for (int j = 1; j <= size; j++) {
            if (arr[i][j] == INF) *fout << "x\t";
            else *fout << arr[i][j] << "\t";
        }
        *fout << endl;
    }
    *fout << "====================\n\n";

    delete[] tempMap;
    for (int i = 1; i <= size; ++i) delete[] arr[i];
    delete[] arr;
    return true;
}

int init(vector<int> kw_graph, int* seg, int node, int start, int end) {
    if (start == end) return seg[node] = 1;
    int mid = (start + end) / 2;
    return seg[node] = init(kw_graph, seg, node * 2, start, mid) + init(kw_graph, seg, node * 2 + 1, mid + 1, end);
}

void update(int node, int start, int end, int target, int diff_val, int* seg) {
    if (target < start || target > end) return;

    seg[node] += diff_val;

    if (start != end) {
        int mid = (start + end) / 2;
        update(node * 2, start, mid, target, diff_val, seg);
        update(node * 2 + 1, mid + 1, end, target, diff_val, seg);
    }
}

int Sum(int Node, int Start, int End, int Left, int Right, vector<int>& seg) {
    if (Left > End || Right < Start) return 0;
    if (Left <= Start && End <= Right) return seg[Node];

    int Mid = (Start + End) / 2;
    int Left_Result = Sum(Node * 2, Start, Mid, Left, Right, seg);
    int Right_Result = Sum(Node * 2 + 1, Mid + 1, End, Left, Right, seg);
    return Left_Result + Right_Result;
}

bool KWANGWOON(Graph* graph, int vertex, ofstream* fout) {
    int size = graph->getSize();
    map<int, int>* tempMap = new map<int, int>[size + 1];
    // with direction
    for (int i = 1; i <= size; i++)
        graph->getAdjacentEdges(i, tempMap);

    vector<int>* kw_graph = new vector<int>[size + 1];
    int** seg = new int*[size + 1];
    bool* visited = new bool[size + 1];

    for (int i = 1; i <= size; i++) {
        visited[i] = false;
        for (auto iter = tempMap[i].begin(); iter != tempMap[i].end(); iter++) {
            // i: from, iter.first: to, iter.second: weight
            kw_graph[i].push_back(iter->first);
        }
        seg[i] = new int[kw_graph[i].size() * 4]; // allocate x4 space for worst case
        memset(seg[i], 0, sizeof(int) * 4 * kw_graph[i].size());
        init(kw_graph[i], seg[i], 1, 0, kw_graph[i].size() - 1); // initialize segment tree
    }

    int curNode = 1;
    queue<int> path;

    while (seg[curNode][1]) { // check segment treee root; if root is 0 break
        path.push(curNode);
        visited[curNode] = true;

        for (int i = 1; i <= size; i++) {
            // visited check
            if (visited[i]) continue;
            auto iter = find(kw_graph[i].begin(), kw_graph[i].end(), curNode);
            // cannot find same node
            if (iter == kw_graph[i].end()) continue;
            update(1, 0, kw_graph[i].size() - 1, iter - kw_graph[i].begin(), -1, seg[i]);
        }

        // if even node is connected
        if (seg[curNode][1] % 2 == 0) {
            int temp;
            for (int j = 0; ; j++) {
                temp = kw_graph[curNode][j];
                if (visited[temp] == false) break;
            }
            curNode = temp;
        }
        // if odd node is connected
        else {
            int temp;
            for (int j = kw_graph[curNode].size() - 1; ; j--) {
                temp = kw_graph[curNode][j];
                if (visited[temp] == false) break;
            }
            curNode = temp;
        }

    }
    path.push(curNode);

    *fout << "========KWANGWOON========\n";
    *fout << "startvertex: " << vertex << endl << vertex;
    path.pop();
    while (!path.empty()) {
        *fout << "->" << path.front();
        path.pop();
    }
    *fout << "\n====================\n\n";


    delete[] tempMap;
    for (int i = 1; i <= size; ++i)
        delete[] seg[i];
    delete[] seg;
    delete[] visited;
    delete[] kw_graph;
    return true;
}
