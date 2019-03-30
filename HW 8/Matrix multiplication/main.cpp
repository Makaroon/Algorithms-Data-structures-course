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

		//Можно сюда передать матрицу и здесь вычислять какие значения выводить в файл.
		//Можно заранее сформировать ответ и здесь его просто выводить построчно. Как вам удобнее.
		//Работать с файлом вот так: 
		//fout<< value1 << value2 << value3;
    }

void solve(int N, int M, vector<Edge>& edges, vector<vector<int>>& result)
{

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