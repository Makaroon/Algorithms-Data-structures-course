#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h
#include <algorithm>
#include <climits>

using namespace std;

// write all values
void ReadWriter::writeValues(std::vector<std::vector<int>>& result)
{
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");

    for (int i = 0; i < result[0].size(); ++i)
        for (int j = 0; j < result[0].size(); ++j)
            if (i != j)
                fout << i << " " << j << " " << result[i][j] << '\n';
}

vector<vector<int>> extendShortestPath(vector<vector<int>>& l, vector<vector<int>>& w)
{
    int N = static_cast<int>(l.size());
    vector<vector<int>> newL(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            newL[i][j] = 130001;
            for (int k = 0; k < N; ++k)
                newL[i][j] = min(newL[i][j], l[i][k] + w[k][j]);
        }
    return newL;
}

///O(|V|^4) realization
void solve(int N, int M, vector<Edge>& edges, vector<vector<int>>& result)
{
    ///initialization
    vector<vector<int>> w(N, vector<int>(N));
    int zeroA = 0, zeroB = 0;
    for (int i = 0; i < edges.size(); ++i)
    {
        w[edges[i].A][edges[i].B] = edges[i].W;
        if (edges[i].W == 0)
        {
            zeroA = edges[i].A;
            zeroB = edges[i].B;
        }
    }
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            if (w[i][j] == 0 && i != j)
                w[i][j] = 130001;
        }
    w[zeroA][zeroB] = 0;

    vector<vector<int>> l = w;
    for (int i = 0; i < N - 2; ++i)
        l = extendShortestPath(l, w);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (l[i][j] == 130001)
                l[i][j] = -1;
    result = l;
}

int main()
{
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    vector<vector<int>> result(N);

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    rw.writeValues(result);

    return 0;
}