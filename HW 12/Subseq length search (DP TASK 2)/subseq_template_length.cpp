#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

int getLCS(const string& x, const string& y)
{
    int xLen = x.length(), yLen = y.length();
    int arr[x.length() + 1][y.length() + 1];

    for (int i = 0; i <= yLen; ++i)
        arr[0][i] = 0;

    for (int i = 1; i <= xLen; ++i)
    {
        arr[i][0] = 0;
        for (int j = 1; j <= yLen; ++j)
        {
            if (x[i - 1] == y[j - 1])
                arr[i][j] = arr[i - 1][j - 1] + 1;
            else
                arr[i][j] = max(arr[i][j - 1], arr[i - 1][j]);
        }
    }

    int i = xLen, j = yLen;
    string out;
    while (arr[i][j] != 0)
    {
        if (arr[i][j] == arr[i - 1][j])
            --i;
        else if (arr[i][j] == arr[i][j - 1])
            --j;
        else
        {
            out = x[i - 1] + out;
            --i;
            --j;
        }
    }

    return out.size();
}

int main()
{
    string x;
    string y;
    int res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, x);
        getline(fin, y);
        fin.close();
    }

    res = getLCS(x, y);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}