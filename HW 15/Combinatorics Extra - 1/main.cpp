#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

string solve(long n, long m, long k)
{
    string out;
    long i = m - 1;

    if (k == 1L)
    {
        for (; i > 0; --i)
            out += "1 ";
        out += '1';
        return out;
    }

    vector<long> res;
    for (k -= 1L; k > 0 && i >= 0; --i, k /= n)
        res.emplace_back(k % n + 1L);
    for (; i >= 0; --i)
        out += "1 ";
    for (i = res.size() - 1; i > 0; --i)
        out += to_string(res[i]) + ' ';
    out += to_string(res[0]);
    return out;
}

int main(int argc, const char* argv[])
{
    long M, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = atol(str.c_str());
        getline(fin, str);
        M = atol(str.c_str());
        getline(fin, str);
        K = atol(str.c_str());
        fout << solve(N, M, K) << endl;
        fout.close();
        fin.close();
    }
    return 0;
}
