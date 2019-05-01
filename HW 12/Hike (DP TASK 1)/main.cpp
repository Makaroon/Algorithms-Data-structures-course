#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Основная задача - реализовать данный метод
int countMaxCross(string& riverMap)
{
    int n = riverMap.length();
    int left[n + 1];
    int right[n + 1];

    left[0] = 0;
    right[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        int stepLeft = left[i - 1], stepRight = right[i - 1];

        if (riverMap[i - 1] == 'L')
            stepLeft++;
        else if (riverMap[i - 1] == 'R')
            stepRight++;
        else if (riverMap[i - 1] == 'B')
        {
            stepLeft++;
            stepRight++;
        }
        left[i] = std::min(stepLeft, stepRight + 1);
        right[i] = std::min(stepRight, left[i] + 1);
    }

    return right[n];
}


int main()
{
    string riverMap;
    int res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, riverMap);
        fin.close();
    }

    res = countMaxCross(riverMap);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}
