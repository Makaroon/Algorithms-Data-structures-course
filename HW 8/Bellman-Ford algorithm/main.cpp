﻿#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

void relax(vector<int>& d, vector<int>& p, int v, int u, int path)
{
    if (d[v] > d[u] + path)
    {
        d[v] = d[u] + path;
        p[v] = u;
    }
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора кратчайших расстояний из 0-й вершины во все остальные начиная с 1-й, то есть N-1 значение должно быть
void solve(int N, int M, vector<Edge>& edges, vector<int>& result)
{
    //initialization
    vector<int> d(N);
    vector<int> p(N);
    for (int i = 0; i < N; ++i)
    {
        d[i] = 30001;
        p[i] = -1;
    }
    d[0] = 0;

    //Bellman-Ford
    for (int i = 0; i < N - 1; ++i)
        for (int j = 0; j < M; ++j)
            relax(d, p, edges[j].B, edges[j].A, edges[j].W);

    for (int i = 0; i < M; ++i)
        if (d[edges[i].B] > d[edges[i].A] + edges[i].W)
            return;

    for (int i = 1; i < N; ++i)
        result.push_back(d[i]);

    d.clear();
    p.clear();
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

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    vector<int> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    //Выводим результаты
    if (!result.empty())
    {
        rw.writeInt(result.size());
        rw.writeIntValues(result);
    }

    return 0;
}