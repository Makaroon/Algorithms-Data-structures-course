﻿#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

///метод для сравнения рёбер по их весам
bool compare(Edge& l, Edge& r)
{
    return l.W < r.W;
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.

/// вдохновлено http://e-maxx.ru/algo/mst_kruskal (решение полностью осмыслено и обдуманно автором)
void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    sort(edges.begin(), edges.end(), compare); //сортировка edges по весам рёбер

    vector<int> comp(N); //содержит номер поддерева для каждой вершины
    int c = 0;
    for (int i = 0; i < N; ++i)
        comp[i] = i;
    for (int j = 0; j < M; ++j)
    {
        int a = edges[j].A, b = edges[j].B, w = edges[j].W;
        if (comp[a] != comp[b])
        {
            c++;
            result.push_back(edges[j]);
            int old_id = comp[b], new_id = comp[a];
            for (int j = 0; j < N; ++j)
                if (comp[j] == old_id)
                    comp[j] = new_id;
        }
    }

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
    //(а предложенные алгоритмы работают итеративно, увеличивая количество ребер входящих в решение на каждом шаге)
    vector<Edge> result;

    //Алгоритм решения задачи
    //В решение должны входить ребра из первоначального набора!
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}