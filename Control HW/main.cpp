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

bool findPath(size_t V, vector<vector<int>>& rGraph, int cur, int t, vector<int>& parent, vector<bool>& visited)
{
    visited[cur] = true;

    for (int i = 0; i < V; ++i)
    {
        if (!visited[i] && rGraph[cur][i] > 0)
        {
            parent[i] = cur;
            bool found = findPath(V, rGraph, i, t, parent, visited);
            if (found)
                return true;
        }
    }

    return visited[t];
}

int solveFordFulkerson(size_t n, vector<vector<int >> x, int s, int t)
{
    int u, v;

    vector<vector<int>> rGraph = x;

    vector<int> parent(n);
    parent[s] = -1;
    int max_flow = 0;

    vector<bool> visited;
    visited.assign(n, 0);

    while (findPath(n, rGraph, s, t, parent, visited))
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
        for (int i = 0; i < n; ++i)
        {
            visited[i] = false;
        }
    }

    return max_flow;
}

bool bfsEK(vector<vector<int>>& x, int a, int b, vector<int>& parent)
{
    bool used[x.size()];
    for (int i = 0; i < x.size(); ++i)
        used[i] = false;

    queue<int> S;
    int max;
    S.push(a);
    do
    {
        max = S.front();
        S.pop();

        for (int j = 0; j < x[max].size(); ++j)
            if (!used[j] && x[max][j] > 0)
            {
                S.push(j);
                parent[j] = max;
                used[j] = true;

            }
    } while (!S.empty());

    return (used[b]);
}

int solveEdmondsKarp(size_t n, vector<vector<int>> x, int a, int b)
{
    int all_flow = 0;
    vector<int> parent(n, -1);
    int max_flow = 0;
    while (bfsEK(x, a, b, parent))
    {
        int path_flow = INT16_MAX;
        int u;
        for (int v = b; v != a; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, x[u][v]);
        }


        for (int v = b; v != a; v = parent[v])
        {
            u = parent[v];
            x[u][v] -= path_flow;
            x[v][u] += path_flow;
        }

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

int solveDinitz(size_t n, vector<vector<int>> x, int a, int b)
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


        int time[3] = {0, 0, 0};
        int res[3] = {0, 0, 0};

        for (int j = 0; j < 10; ++j)
        {
            auto beginFF = std::chrono::steady_clock::now();
            res[0] = solveFordFulkerson(x.size(), x, firstPoint, lastPoint);
            auto endFF = std::chrono::steady_clock::now();
            auto workTimeFF = std::chrono::duration_cast<std::chrono::nanoseconds>(endFF - beginFF);
            time[0] += workTimeFF.count();

            auto beginEK = std::chrono::steady_clock::now();
            res[1] = solveEdmondsKarp(x.size(), x, firstPoint, lastPoint);
            auto endEK = std::chrono::steady_clock::now();
            auto workTimeEK = std::chrono::duration_cast<std::chrono::nanoseconds>(endEK - beginEK);
            time[1] += workTimeEK.count();

            auto beginD = std::chrono::steady_clock::now();
            res[2] = solveDinitz(x.size(), x, firstPoint, lastPoint);
            auto endD = std::chrono::steady_clock::now();
            auto workTimeD = std::chrono::duration_cast<std::chrono::nanoseconds>(endD - beginD);
            time[2] += workTimeD.count();
        }
        cout << names[i] << " RESULT: " << res[0] << " " << res[1] << " " << res[2]
             << "\nTIME " << time[0]/10 << " " << time[1]/10 << " " << time[2]/10 << "\n";
    }
    return 0;
}