#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

void ReadWriter::writeValues(std::vector<std::vector<int>> result)
{
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");

    for (int i = 0; i < result[0].size(); ++i)
        for (int j = 0; j < result[0].size(); ++j)
            if (i != j)
                fout << i << " " << j << " " << result[i][j] << '\n';
}

void relax(vector<int>& d, vector<int>& p, int v, int u, int path)
{
    if (d[v] > d[u] + path)
    {
        d[v] = d[u] + path;
        p[v] = u;
    }
}

///check if we entered all vertices
bool allUsed(vector<bool>& used)
{
    bool flag = true;
    for (bool b : used)
        if (!b)
            flag = false;
    return flag;
}

///finding unused vertex with minimal distance
///returning index of the vertex
int findMin(vector<int>& d, vector<bool>& used, int N)
{
    int min = 30001;
    int num = -1;
    for (int i = 0; i < N; ++i)
        if (!used[i])
            if (d[i] < min)
            {
                num = i;
                min = d[i];
            }
    return num;
}

void algBF(int N, int M, vector<Edge>& edges, vector<int>& result)
{
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

    for (int i = 1; i < N; ++i)
        result.push_back(d[i]);
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
void solve(int N, int M, vector<Edge>& edges, vector<vector<int>>& result)
{
    ///initialization
    vector<vector<int>> D(N, vector<int>(N));


    for (int i = 0; i < N; ++i)
    {
        Edge e;
        e.A=N;
        e.B=i;
        e.W=0;
        e.number=edges.size();
        edges.push_back(e);
    }

    vector<int> h;
    ///..
    algBF(N, static_cast<int>(edges.size()), edges, h);

    for (int i = 0; i < edges.size(); ++i)
        edges[i].W+=h[edges[i].A]-h[edges[i].B];

    for(int i=0;i<N+1;++i)
    {
        vector<vector<int>> s;
        ///..
        for(int j=0;j<N+1;++j)
            D[i][j]=s[i][j]+h[j]-h[i];
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
    vector<vector<int>> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeValues(result);

    return 0;
}