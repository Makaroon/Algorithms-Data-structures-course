#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

///Function to count prefixes
vector<int> prefixFunction(string& s, int n, vector<int>& pref)
{
    int j = 0;
    for (int i = 1; i < n; ++i)
    {
        while (j > 0 && s[i] != s[j])
            j = pref[j - 1];
        if (s[i] == s[j]) ++j;
        pref[i] = j;
    }

    return pref;
}

//Основная задача - реализовать данный метод
//Можно изменить передачу параметров на ссылки (&)
//Можно добавлять любое количество любых вспомогательных методов, структур и классов

///Inspired by Cormen - Introduction to algorithms
void getSubstrings(string& source, string& substring, vector<int>& res)
{
    int n = (int) source.length(), k = (int) substring.length(), q = 0;
    vector<int> pref(k);
    prefixFunction(substring, k, pref);
    for (int i = 0; i < n; ++i)
    {
        while (q > 0 && substring[q] != source[i])
            q = pref[q - 1];
        if (substring[q] == source[i])
            q++;
        if (q == k)
        {
            res.push_back(i - k + 1);
            q = pref[q - 1];
        }
    }

    pref.clear();
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
    string t;
    string p;
    vector<int> res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, t);
        getline(fin, p);
        fin.close();
    }

    getSubstrings(t, p, res);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res.size() << "\n";
    for (std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i)
        fout << *i << "\n";
    fout.close();

    return 0;
}
