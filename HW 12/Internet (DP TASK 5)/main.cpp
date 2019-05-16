#include <iostream>
#include <fstream>
#include <vector>


using namespace std;


int countMinSum(int seconds, vector<int>& values)
{
    for (int i = 1; i < values.size(); ++i)
    {
        if (values[i] < values[i - 1] * 2)
            values[i] = values[i - 1] * 2;
    }
    int count = 0;
    for (int i = 30; i >= 0; --i)
    {
        if (seconds >= values[i])
        {
            seconds -= values[i];
            count += count << i;
        }
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
