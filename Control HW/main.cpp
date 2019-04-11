#include <iostream>
#include <queue>
#include<ctime>
#include <chrono>
#include <memory.h>
#include "ReadWriter.h"

/// КДЗ по дисциплине Алгоритмы и структуры данных, 2018-2019 уч.год
/// Ясиновский Александр Кириллович, группа БПИ-172, 01.04.2019
// Среда разработки, состав проекта (файлы *.cpp и *.h)
// Что сделано, а что нет


using namespace std;
const int INF = 1000000000; // константа-бесконечность

int findFirst(vector<vector<int>>& x)
{
    bool check;
    for (int i = 0; i < x.size(); ++i)
    {
        check = true;
        for (auto& j : x)
            if (j[i] != 0)
                check = false;
        if (check)
            return i;
    }
    return -1;
}

int findLast(vector<vector<int>>& x)
{
    bool check;
    for (int i = 0; i < x.size(); ++i)
    {
        check = true;
        for (int j = 0; j < x.size(); ++j)
            if (x[i][j] != 0)
                check = false;
        if (check)
            return i;
    }
    return -1;
}

bool find_path(size_t V, vector<vector<int>>& rGraph, int cur, int t, vector<int>& parent, vector<bool>& visited)
{
    visited[cur] = true;

    for (int i = 0; i < V; ++i)
    {
        if (!visited[i] && rGraph[cur][i] > 0)
        {
            parent[i] = cur;
            bool found = find_path(V, rGraph, i, t, parent, visited);
            if (found)
                return true;
        }
    }

    return visited[t];
}

int solveFordFulkerson(size_t V, vector<vector<int >>& graph, int s, int t)
{
    int u, v;

    vector<vector<int>> rGraph = graph;

    vector<int> parent(V);
    parent[s] = -1;
    int max_flow = 0;

    vector<bool> visited;
    visited.assign(V, 0);

    while (find_path(V, rGraph, s, t, parent, visited))
    {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
        for (int i = 0; i < V; ++i)
        {
            visited[i] = false;
        }
    }

    return max_flow;
}

bool bfsEK(vector<vector<int>> r, int a, int b, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    bool visited[r.size()];
    for (bool bb : visited)
        bb = false;
    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue<int> q;
    q.push(a);
    visited[a] = true;
    parent[a] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < r.size(); v++)
        {
            if (!visited[v] && r[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    return visited[b];
}

int solveEdmondsKarp(size_t n, vector<vector<int>>& x, int a, int b)
{
    int u, v;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    vector<vector<int>> r(n, vector<int>(n)); // Residual graph where rGraph[i][j] indicates
    // residual capacity of edge from i to j (if there
    // is an edge. If rGraph[i][j] is 0, then there is not)
    for (u = 0; u < n; u++)
        for (v = 0; v < n; v++)
            r[u][v] = x[u][v];
    // Augment the flow while tere is path from source to sink

    // Find minimum residual capacity of the edges along the
    // path filled by BFS. Or we can say find the maximum flow
    // through the path found.
    int parent[n];  // This array is filled by BFS and to store path
    int max_flow = 0;  // There is no flow initially

    while (bfsEK(r, a, b, parent))
    {
        int path_flow = INT_MAX;
        for (v = b; v != a; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, r[u][v]);
        }

        // update residual capacities of the edges and reverse edges
        // along the path
        for (v = b; v != a; v = parent[v])
        {
            u = parent[v];
            r[u][v] -= path_flow;
            r[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }
    return max_flow;
}

bool bfs(vector<vector<int>>& x, int n, int a, int b, int* d, int* q, vector<vector<int>>& f)
{
    int qh = 0, qt = 0;
    q[qt++] = a;
    memset(d, -1, n * sizeof d[0]);
    d[a] = 0;
    while (qh < qt)
    {
        int v = q[qh++];
        for (int to = 0; to < n; ++to)
            if (d[to] == -1 && f[v][to] < x[v][to])
            {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
    }
    return d[b] != -1;
}

int dfs(int v, int flow, int n, int b, int* ptr, int* d, vector<vector<int>>& x, vector<vector<int>>& f)
{
    if (!flow) return 0;
    if (v == b) return flow;
    for (int& to = ptr[v]; to < n; ++to)
    {
        if (d[to] != d[v] + 1) continue;
        int pushed = dfs(to, min(flow, x[v][to] - f[v][to]), n, b, ptr, d, x, f);
        if (pushed)
        {
            f[v][to] += pushed;
            f[to][v] -= pushed;
            return pushed;
        }
    }
    return 0;
}

int solveDinitz(size_t n, vector<vector<int>>& x, int a, int b)
{
    int ptr[n];
    vector<vector<int>> f(n, vector<int>(n));
    int d[n];
    int q[n];
    int flow = 0;
    for (;;)
    {
        if (!bfs(x, n, a, b, d, q, f)) break;
        memset(ptr, 0, n * sizeof ptr[0]);
        while (int pushed = dfs(a, INF, n, b, ptr, d, x, f))
            flow += pushed;
    }
    return flow;
}


int main()
{
    string names[40] = {"input_10_0.0.txt", "input_10_0.5.txt", "input_10_1.0.txt", "input_10_disco.txt",
                        "input_310_0.0.txt", "input_310_0.5.txt", "input_310_1.0.txt", "input_310_disco.txt",
                        "input_610_0.0.txt", "input_610_0.5.txt", "input_610_1.0.txt", "input_610_disco.txt",
                        "input_910_0.0.txt", "input_910_0.5.txt", "input_910_1.0.txt", "input_910_disco.txt",
                        "input_1210_0.0.txt", "input_1210_0.5.txt", "input_1210_1.0.txt", "input_1210_disco.txt",
                        "input_1510_0.0.txt", "input_1510_0.5.txt", "input_1510_1.0.txt", "input_1510_disco.txt",
                        "input_1810_0.0.txt", "input_1810_0.5.txt", "input_1810_1.0.txt", "input_1810_disco.txt",
                        "input_2110_0.0.txt", "input_2110_0.5.txt", "input_2110_1.0.txt", "input_2110_disco.txt",
                        "input_2410_0.0.txt", "input_2410_0.5.txt", "input_2410_1.0.txt", "input_2410_disco.txt",
                        "input_2710_0.0.txt", "input_2710_0.5.txt", "input_2710_1.0.txt", "input_2710_disco.txt"};


    for (int i = 0; i < 40; ++i)
    {
        //Запись в матрицу
        ReadWriter rw(names[i]);
        vector<vector<int >> x;
        rw.read(x, names[i]);
        int firstPoint = findFirst(x);
        int lastPoint = findLast(x);

        auto timeFF = 0;
        int res = 0;

        auto beginFF = std::chrono::steady_clock::now();
        res = solveEdmondsKarp(x.size(), x, firstPoint, lastPoint);
        auto endFF = std::chrono::steady_clock::now();
        auto workTimeFF = std::chrono::duration_cast<std::chrono::nanoseconds>(endFF - beginFF);
        timeFF += workTimeFF.count();
        cout << names[i] << " RESULT: " << res << " TIME " << timeFF << "\n";
    }


//    auto ts3 = double(clock());

//    int res1 = solveFordFulkerson(x, firstPoint, lastPoint);
//    auto te1 = double(clock());
//    double t1 = ((te1 - ts1) / CLOCKS_PER_SEC); // время в секундах
//    std::cout << "Ford-Fulkerson max flow: " << res1 << "\tTim//    int res3 = solveDinitz(x, firstPoint, lastPoint);
//    auto te3 = double(clock());
//    double t3 = ((te3 - ts3) / CLOCKS_PER_SEC); // время в секундах
//    std::cout << "Dinitz max flow: " << res3 << "\tTime: " << t3 << "\n";
    return 0;
}