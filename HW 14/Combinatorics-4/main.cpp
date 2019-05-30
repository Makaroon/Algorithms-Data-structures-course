#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

void getNext(int* a, int N, int k)
{
    int i = k - 1;
    while (N < a[i] + k - i)
        --i;
    ++a[i];
    for (int j = i + 1; j < k; ++j)
        a[j] = a[j - 1] + 1;
}


//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get(int N, int k, int m)
{
    int a[m];
    for (int i = 0; i < m; ++i)
        a[i] = i + 1;
    for (int i = 1; i < k; ++i)
        getNext(a, N, m);
    string res;
    for (int i = 0; i < m - 1; ++i)
        res += to_string(a[i]) + ' ';
    res += to_string(a[m - 1]);
    return res;
}

int main(int argc, const char* argv[])
{
    int M, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());
        getline(fin, str);
        K = atoi(str.c_str());
        getline(fin, str);
        M = atoi(str.c_str());
        fout << get(N, K, M) << endl;

        fout.close();
        fin.close();
    }
    return 0;
}