#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

void ReadWriter::writeValues(std::vector<std::vector<int>> result)
{
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");

	//Здесь вывод на печать, например так:
	//Предлагается построчно выводить, как требуется в ответе
	
    for (int i = 0; i < result.size() - 1; i++)
        fout << result[i][0] << ' ' << result[i][1] << ' ' << result[i][2] << "\n";

    fout << result[result.size() - 1][0] << ' ' << result[result.size() - 1][1] << ' ' << result[result.size() - 1][2];
	//Можно сделать иначе - в этом же методе, но используя данные параметры метода (vector<vector<int>>)
	//Для этого метод и вынесен в этот файл
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
void solve(int N, int M, vector<Edge>& edges, vector<vector<int>>& result)
{
    //Советую разделить решение на логические блоки

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