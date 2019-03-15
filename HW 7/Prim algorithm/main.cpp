#include "ReadWriter.h"
#include <set>
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    //Советую разделить решение на логические блоки
    //Можно использовать любые другие структуры, но затем скопировать ответ в структуру Edge для записи результата в файл.
    //Также можно добавить любые необходимые компараторы для предложенного класса Edge, так как все методы и поля публичные.

    vector<vector<int>> graph(N);
    for (int i = 0; i < M; ++i)
    {
        graph[edges[i].A].emplace_back(i);
        graph[edges[i].B].emplace_back(i);
    }

    vector<int> min(N, -1);
    min[0] = -2;
    set<pair<int, int>> connections;
    connections.insert(make_pair(0, 0));
    for (int i = 0; i < N; ++i)
    {
        if (connections.empty())
            return;

        int point = connections.begin()->second;
        connections.erase(connections.begin());
        if (min[point] >= 0)
        {
            result.emplace_back(edges[min[point]]);
            min[point] = -2;
        }

        for (int j : graph[point])
        {
            int dest;
            Edge e = edges[j];
            if (point == e.A)
                dest = e.B;
            else dest = e.A;
            if ((min[dest] >= 0 && e.W < edges[min[dest]].W) || min[dest] == -1)
            {
                connections.erase(make_pair(edges[min[dest]].W, dest));
                min[dest] = e.number;
                connections.insert(make_pair(e.W, dest));
            }
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