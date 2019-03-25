#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

///relaxation
void relax(vector<int>& d, vector<int>& p, int v, int u, int path)
{
    if (d[v] > d[u]+ path)
    {
        d[v] = d[u]+ path;
        p[v] = u;
    }
}

///check if we entered all vertices
bool allUsed(vector<bool>& used)
{
    bool flag=true;
    for(bool b : used)
        if (!b)
            flag=false;
    return flag;
}

///finding unused vertex with minimal distance
///returning index of the vertex
int findMin(vector<int>& d, vector<bool>& used, int N)
{
    int min=30001;
    int num=-1;
    for (int i = 0; i < N; ++i)
        if (!used[i])
            if(d[i]<min)
            {
                num = i;
                min = d[i];
            }
    return num;
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора кратчайших расстояний из 0-й вершины во все остальные начиная с 1-й, то есть N-1 значение должно быть
void solve(int N, int M, vector<Edge>& edges, vector<int>& result)
{
    ///initialization
    vector<int> d(N,30001);
    vector<int> p(N,-1);
    vector<bool> used(N,false);
    d[0] = 0;

    ///Dijkstra alg
    while(!allUsed(used))
    {
        int minVert = findMin(d,used,N);
        used[minVert]=true;
        for (int i=0;i<M;++i)
            if (edges[i].A==minVert)
                relax(d,p,edges[i].B,edges[i].A,edges[i].W);
    }

    ///writing to result vector
    for (int i = 1; i < N; ++i)
        result.push_back(d[i]);

    ///no mem leak
    d.clear();
    p.clear();
    used.clear();
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
    rw.writeInt(result.size());
    rw.writeIntValues(result);

    return 0;
}