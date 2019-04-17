#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

//Основная задача - реализовать данный метод
//Можно изменить передачу параметров на ссылки (&)
//Можно добавлять любое количество любых вспомогательных методов, структур и классов
void getSubstrings(string& source, string& substring, vector<int>& res)
{
    unsigned long long int k = substring.length();
    unsigned long long int n = k + source.length() + 1;
    string s = substring + "\n" + source;
    if(k == 0)
        return;

    int* pref = new int[n];
    pref[0] = 0;
    for(int i = 1; i < n; ++i)
    {
        int j = pref[i - 1];
        while(j > 0 && s[i] != s[j])
            j = pref[j - 1];
        pref[i] = s[i] == s[j] ? ++j : j;
        if(j == k)
            res.push_back(static_cast<int&&>(i - 2 * k));
    }

    delete[] pref;
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
