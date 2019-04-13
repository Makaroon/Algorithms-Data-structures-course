#include <iostream>
#include <queue>
#include<ctime>
#include <chrono>
#include <memory.h>
#include "ReadWriter.h"

/// КДЗ по дисциплине Алгоритмы и структуры данных, 2018-2019 уч.год
/// Ясиновский Александр Кириллович, группа БПИ-172, 12.04.2019
/// IDE: CLion, Project contains of main.cpp, ReadWriter.h and input files
/// DONE: Ford-Fulkerson, Edmonds-Karp, Dinitz algs
/// TODO: Simplex method algorithm based on linear programming


using namespace std;
const int INF = 1000000000; ///const infinity

///finding starting point
vector<int> findFirst(vector<vector<int>>& x)
{
    vector<int> f;
    bool check;
    for (int i = 0; i < x.size(); ++i)
    {
        check = true;
        for (auto& j : x)
            if (j[i] != 0)
                check = false;
        if (check)
            f.push_back(i);
    }
    return f;
}

///finding end point
vector<int> findLast(vector<vector<int>>& x)
{
    vector<int>l;
    bool check;
    for (int i = 0; i < x.size(); ++i)
    {
        check = true;
        for (int j = 0; j < x.size(); ++j)
            if (x[i][j] != 0)
                check = false;
        if (check)
            l.push_back(i);
    }
    return l;
}

///DFS for Ford-Fulkerson algo
bool FFdfs(size_t n, vector<vector<int>>& rGraph, int cur, int b, vector<int>& parent, vector<bool>& visited)
{
    visited[cur] = true;

    for (int i = 0; i < n; ++i)
    {
        if (!visited[i] && rGraph[cur][i] > 0)
        {
            parent[i] = cur;
            bool found = FFdfs(n, rGraph, i, b, parent, visited);
            if (found)
                return true;
        }
    }

    return visited[b];
}

/// Ford-Fulkerson algorithm
/// Realization inspired by Cormen - Introduction to algorithms
int solveFordFulkerson(size_t n, vector<vector<int >> x, vector<int> a, vector<int> b)
{
    int full_flow=0;
    for(int k=0;k<a.size();++k)
    {
        int u, v;

        vector<vector<int>> rGraph = x;

        vector<int> parent(n);
        parent[a[k]] = -1;
        int max_flow = 0;

        vector<bool> visited;
        visited.assign(n, 0);

        while (FFdfs(n, rGraph, a[k], b[k], parent, visited))
        {
            int path_flow = INF;
            for (v = b[k]; v != a[k]; v = parent[v])
            {
                u = parent[v];
                path_flow = min(path_flow, rGraph[u][v]);
            }

            for (v = b[k]; v != a[k]; v = parent[v])
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

        full_flow+= max_flow;
    }
    return full_flow;
}

///BFS for Edmonds-Karp algo
bool EKbfs(vector<vector<int>>& x, int a, int b, vector<int>& parent)
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

///Edmonds-Karp algorithm
///Realization insipred by Cormen - Introduction to algorithms & Wikipedia - "Edmonds-Karp algorithm"
int solveEdmondsKarp(size_t n, vector<vector<int>> x, vector<int> a, vector<int> b)
{
    int full_flow=0;
    for(int k=0;k<a.size();++k)
    {
        int all_flow = 0;
        vector<int> parent(n, -1);
        int max_flow = 0;
        while (EKbfs(x, a[k], b[k], parent))
        {
            int path_flow = INT16_MAX;
            int u;
            for (int v = b[k]; v != a[k]; v = parent[v])
            {
                u = parent[v];
                path_flow = min(path_flow, x[u][v]);
            }


            for (int v = b[k]; v != a[k]; v = parent[v])
            {
                u = parent[v];
                x[u][v] -= path_flow;
                x[v][u] += path_flow;
            }

            max_flow += path_flow;
        }

        full_flow+=max_flow;
    }
    return full_flow;
}

///BFS for Dinitz algo
bool Dbfs(vector<vector<int>>& x, int n, int a, int b, int* d, int* q, vector<vector<int>>& f)
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

///DFS for Dinitz algor
int Ddfs(int v, int flow, int n, int b, int* ptr, int* d, vector<vector<int>>& x, vector<vector<int>>& f)
{
    if (!flow) return 0;
    if (v == b) return flow;
    for (int& to = ptr[v]; to < n; ++to)
    {
        if (d[to] != d[v] + 1) continue;
        int pushed = Ddfs(to, min(flow, x[v][to] - f[v][to]), n, b, ptr, d, x, f);
        if (pushed)
        {
            f[v][to] += pushed;
            f[to][v] -= pushed;
            return pushed;
        }
    }
    return 0;
}

///Dinitz algorithm
///Realization inspired by http://e-maxx.ru/algo/dinic
int solveDinitz(size_t n, vector<vector<int>> x, vector<int> a, vector<int> b)
{
    int full_flow=0;
    for(int k=0;k<a.size();++k)
    {
        int ptr[n];
        vector<vector<int>> f(n, vector<int>(n));
        int d[n];
        int q[n];
        int flow = 0;
        for (;;)
        {
            if (!Dbfs(x, n, a[k], b[k], d, q, f)) break;
            memset(ptr, 0, n * sizeof ptr[0]);
            while (int pushed = Ddfs(a[k], INF, n, b[k], ptr, d, x, f))
                flow += pushed;
        }
        full_flow+= flow;
    }
    return full_flow;
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
        ///Writing inputs to matrix
        ReadWriter rw(names[i]);
        vector<vector<int >> x;
        rw.read(x, names[i]);
        vector<int> firstPoints = findFirst(x);
        vector<int> lastPoints = findLast(x);

        int time[3] = {0, 0, 0};
        int res[3] = {0, 0, 0};

        for (int j = 0; j < 10; ++j)
        {
            ///Counting Ford-Fulkerson alg
            auto beginFF = std::chrono::steady_clock::now();
            res[0] = solveFordFulkerson(x.size(), x, firstPoints, lastPoints);
            auto endFF = std::chrono::steady_clock::now();
            auto workTimeFF = std::chrono::duration_cast<std::chrono::nanoseconds>(endFF - beginFF);
            time[0] += workTimeFF.count();

            ///Counting Edmonds-Karp alg
            auto beginEK = std::chrono::steady_clock::now();
            res[1] = solveEdmondsKarp(x.size(), x, firstPoints, lastPoints);
            auto endEK = std::chrono::steady_clock::now();
            auto workTimeEK = std::chrono::duration_cast<std::chrono::nanoseconds>(endEK - beginEK);
            time[1] += workTimeEK.count();

            ///Counting Dinitz alg
            auto beginD = std::chrono::steady_clock::now();
            res[2] = solveDinitz(x.size(), x, firstPoints, lastPoints);
            auto endD = std::chrono::steady_clock::now();
            auto workTimeD = std::chrono::duration_cast<std::chrono::nanoseconds>(endD - beginD);
            time[2] += workTimeD.count();
        }
        cout << names[i] << " RESULT: " << res[0] << " " << res[1] << " " << res[2]
             << "\nTIME " << time[0] / 10 << " " << time[1] / 10 << " " << time[2] / 10 << "\n";
    }
    return 0;
}