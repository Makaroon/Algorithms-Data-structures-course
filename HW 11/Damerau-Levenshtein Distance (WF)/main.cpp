#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//Необходимо реализовать метод
//о алгоритме можно прочитать в источниках указанных в программе курса, или на странице курса в ЛМС или в презентациях к семинару.

///Inspired by http://qaru.site/questions/592078/damerau-levenshtein-distance-edit-distance-with-transposition-c-implementation
int Wagner_Fischer_for_Damerau_Levenshtein(string& s, string& t)
{
    int n = s.length(), m = t.length();
    int d[n + 1][m + 1];
    int d1, d2, d3;

    for (int i = 0; i <= m; ++i)
        d[0][i] = i;

    for (int i = 1; i <= n; i++)
    {
        d[i][0] = i;
        for (int j = 1; j <= m; j++)
        {
            d1 = d[i - 1][j] + 1;
            d2 = d[i][j - 1] + 1;
            d3 = d[i - 1][j - 1] + (int) (s[i - 1] != t[j - 1]);
            d[i][j] = min(min(d1, d2), d3);

            ///transposition
            if (i > 1 && j > 1 && s[i - 1] == t[j - 2] && s[i - 2] == t[j - 1])
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + 1);
        }
    }
    return d[n][m];
}


//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main(int argc, const char* argv[])
{
    int n;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string N;
        getline(fin, N);
        n = atoi(N.c_str());
        for (int i = 0; i < n; i++)
        {
            string s;
            string t;
            getline(fin, s);
            getline(fin, t);
            fout << Wagner_Fischer_for_Damerau_Levenshtein(s, t) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }
    return 0;
}