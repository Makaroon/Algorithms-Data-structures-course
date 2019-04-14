#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int* prefixFunction(string s, int n)
{
    int* pref = new int[n];
    pref[0] = 0;
    for (int i = 1; i < n; ++i)
    {
        int j = pref[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pref[j - 1];
        pref[i] = s[i] == s[j] ? ++j : j;
    }
    return pref;
}

//Основная задача - реализовать данный метод
//Результат поместить в переменную res, она как раз доступна для изменения
//Можно добавлять любое количество любых вспомогательных методов, структур и классов
void getBorders(string& s, string& res)
{
    int n = s.length();
    int* pref = prefixFunction(s, n);

    int i = pref[n - 1], k = -1;
    int* r = new int[i];
    while (i != 0)
    {
        r[++k] = i;
        i = pref[i - 1];
    }

    for (int j = k; j >= 0; --j)
        res += s.substr(0, r[j]) + "\n";

    delete[] pref;
    delete[] r;
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
    string input;
    string res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, input);
        fin.close();
    }

    getBorders(input, res);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}
