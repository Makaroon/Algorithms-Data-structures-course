#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

void nextPermutation(int* p, int n)
{
    int i = n - 1, j = n - 1;
    while (i > 0 && p[i] < p[i - 1])
        --i;
    while (p[j] < p[i - 1])
        --j;
    swap(p[i - 1], p[j]);
    for (int k = 0; k < (n - i + 1) / 2; ++k)
        swap(p[i + k], p[n - k - 1]);
}

//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get_day(int N, int k)
{
    int a[N];
    for (int i = 0; i < N; ++i)
        a[i] = i + 1;

    for (int i = 1; i < k; ++i)
        nextPermutation(a, N);

    string s;
    for (int i = 0; i < N - 1; ++i)
        s += to_string(a[i]) + " ";
    return s + to_string(a[N - 1]);
}

int main(int argc, const char* argv[])
{

    int N, K;
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
        fout << get_day(N, K) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}
