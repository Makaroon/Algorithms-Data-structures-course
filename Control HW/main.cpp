#include <iostream>
#include <queue>
#include<ctime>
#include "ReadWriter.h"

/// КДЗ по дисциплине Алгоритмы и структуры данных, 2018-2019 уч.год
/// Ясиновский Александр Кириллович, группа БПИ-172, 01.04.2019
// Среда разработки, состав проекта (файлы *.cpp и *.h)
// Что сделано, а что нет


using namespace std;

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

bool bfs(vector<vector<int>> r, int a, int b, int parent[])
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

int solveFordFulkerson(vector<vector<int>> x, int a, int b)
{
    return 0;
}

int solveEdmondsKarp(vector<vector<int>>& x, int a, int b)
{
    int u, v;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    vector<vector<int>> r(x.size(), vector<int>(x.size())); // Residual graph where rGraph[i][j] indicates
    // residual capacity of edge from i to j (if there
    // is an edge. If rGraph[i][j] is 0, then there is not)
    for (u = 0; u < x.size(); u++)
        for (v = 0; v < x.size(); v++)
            r[u][v] = x[u][v];
    // Augment the flow while tere is path from source to sink

    // Find minimum residual capacity of the edges along the
    // path filled by BFS. Or we can say find the maximum flow
    // through the path found.
    int parent[x.size()];  // This array is filled by BFS and to store path

    int max_flow = 0;  // There is no flow initially

    while (bfs(r, a, b, parent))
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

int solveDinitz(vector<vector<int>>& x, int a, int b)
{
    return 0;
}

int main()
{
    //Запись в матрицу
    ReadWriter rw;
    vector<vector<int>> x;
    rw.read(x);

    int firstPoint = findFirst(x);
    int lastPoint = findLast(x);


//    auto ts1 = double(clock());e: " << t1 << "\n";


    auto ts2 = double(clock());
    int res2 = solveEdmondsKarp(x, firstPoint, lastPoint);
    auto te2 = double(clock());
    double t2 = ((te2 - ts2) / CLOCKS_PER_SEC); // время в секундах
    std::cout << "Edmonds-Karp max flow: " << res2 << "\tTime: " << t2 << "\n";

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