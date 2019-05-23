#include "ReadWriter.h"
//string, iostream included in "ReadWriter.h"

using namespace std;


//Можно добавлять любые вспомогательные методы и классы для решения задачи.
long long** b;

long long count(int i, int j, int N, int M)
{
    if(i < 0 || j < 0 || i >= N || j >= M)
        return 0;

    if(b[i][j] != -1)
        return b[i][j];

    if(i == 0)
        return b[i][j] = j >= 2 ? count(i + 1, j - 2, N, M) : 0;
     else if(i == 1)
        return b[i][j] = j >= 2 ? count(i + 1, j - 2, N, M) + count(i - 1, j - 2, N, M) : 0;
    if(j == 0)
        return b[i][j] = i >= 2 ? count(i - 2, j + 1, N, M) : 0;
    else if(j == 1)
        return b[i][j] = i >= 2 ? count(i - 2, j - 1, N, M) + count(i - 2, j + 1, N, M) : 0;

    return b[i][j] = count(i + 1, j - 2, N, M) + count(i - 1, j - 2, N, M)
                         + count(i - 2, j - 1, N, M) + count(i - 2, j + 1, N, M);
}

//Задача реализовать этот метод
//param N - количество строк (rows) доски
//param M - количество столбцов (columns) доски
//return - количество способов попасть в правый нижний угол доски (клетка N-1, M-1, если считать что первая клетка 0,0)
long long solve(int N, int M)
{
    b = new long long*[N];
    for(int i = 0; i < N; ++i)
    {
        b[i] = new long long[M];
        for(int j = 0; j < M; ++j)
            b[i][j] = -1;
    }
    b[0][0] = 1;
    long long res = count(N - 1, M - 1, N, M);
    for(int i = 0; i < N; ++i)
        delete[] b[i];
    delete[] b;
    return res;
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;

    int N = rw.readInt(); //количество строк (rows)
    int M = rw.readInt(); //количество столбцов (columns)
    //решение
    long long res = solve(N, M);
    //результат в файл
    rw.writeLongLong(res);

    return 0;
}