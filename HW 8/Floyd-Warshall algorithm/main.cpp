#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

//Так как здесь есть несколько способов вывода ответа, то я предлагаю вам самим реализовать метод вывода,
//определенный в классе ReadWriter.
//Можно прямо сюда закинуть матрицу, и потом вычислять какие значения записывать в файл,
//или сначала сформировать вывод в каком-то вспомогательном методе и затем здесь только отправлять в файл.

///writing result to a file
void ReadWriter::writeValues(std::vector<std::vector<int>> result)
{
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");

    for (int i = 0; i < result[0].size(); ++i)
        for (int j = 0; j < result[0].size(); ++j)
            if (i != j)
                fout << i << " " << j << " " << result[i][j] << '\n';
}


//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
void solve(int N, int M, vector<Edge>& edges, vector<vector<int>>& matrix)
{
    ///initialization
    matrix = vector<vector<int>>(N, vector<int>(N));
    vector<vector<int>> D(N, vector<int>(N));
    vector<vector<int>> P(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            P[i][j] = -1;
            if (i != j)
                D[i][j] = 130001;
        }
    for (int i = 0; i < edges.size(); ++i)
    {
        D[edges[i].A][edges[i].B] = edges[i].W;
        P[edges[i].A][edges[i].B] = edges[i].A;
    }

    ///Floyd-Warshall algorithm
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (D[i][j] > D[i][k] + D[k][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }

    ///Changing impossible paths to -1 value (necessary for task)
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (D[i][j] == 130001)
                D[i][j] = -1;

    matrix = D;

    ///mem clear
    D.clear();
    P.clear();
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
    vector<vector<int>> result(N);

    //Алгоритм решения задачи
    solve(N, M, edges, result);
    //Здесь можно вызвать ещё какой-то метод, если вам требуется.

    rw.writeValues(result);

    return 0;
}