#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

string solve(long n, long k)
{
    string out;
    long m = n;

    if (k == 1L)
    {
        for (; m > 1; --m)
            out += "1 ";
        out += '1';
        return out;
    }

    vector<long> res;
    for (k -= 1L; k > 0 && m >= 1; k /= m--)
        res.emplace_back(k % m + 1L);
    for (; m >= 1; --m)
        out += "1 ";
    for (m = res.size() - 1; m > 0; --m)
        out += to_string(res[m]) + ' ';
    out += to_string(res[0]);
    return out;
}

//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)

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
        fout << solve(N, K) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}
