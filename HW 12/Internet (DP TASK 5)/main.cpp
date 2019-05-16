#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


using namespace std;

int getMinIndex(vector<float> c)
{
    int min = 10000000;
    int index = -1;
    for (int i = 0; i < c.size(); ++i)
        if (c[i] < min)
        {
            min = c[i];
            index = i;
        }
    return index;
}

int getMax(vector<float> c)
{
    int max = -1;
    int index = -1;
    for (int i = 0; i < c.size(); ++i)
        if (c[i] > max)
        {
            max = c[i];
            index = i;
        }
    return max;
}

int countMinSum(int seconds, vector<int>& values)
{
    vector<float> c;
    int count = 0;
    for (int i = 0; i < values.size(); ++i)
    {
        c.push_back(pow(2, i) / values[i]);
    }

    while (seconds > 0)
    {
        seconds -= (values[getMinIndex(c)]);
        count += pow(2, getMinIndex(c));
        if (seconds - values[getMinIndex(c)] < 0)
            c[getMinIndex(c)] += getMax(c);
    }
    return count;
}


int main()
{
    vector<int> values;
    int value = 0, seconds = 0;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        fin >> seconds;
        for (int i = 0; i < seconds; i++)
        {
            fin >> value;
            values.push_back(value);
        }
        fin.close();
    }

    int res = countMinSum(seconds, values);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}
