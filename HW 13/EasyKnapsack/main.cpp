#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void solve(int N, int W, pair<int, int>* items, int& res)
{
    int a[N + 1][W + 1];

    for (int j = 1; j <= N; j++)
        a[j][0] = 0;

    for (int i = 0; i <= W; i++)
        a[0][i] = 0;

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= W; ++j)
        {
            if (j - items[i - 1].first >= 0)
                a[i][j] = max(a[i - 1][j - items[i - 1].first] + items[i - 1].second, a[i - 1][j]);
            else
                a[i][j] = a[i - 1][j];
        }

    int i = N, j = W;

    do
        if (a[i][j] != a[i - 1][j])
        {
            j -= items[i - 1].first;
            res += items[i - 1].second;
        }
    while (a[--i][j] > 0);
}

int main()
{
    ifstream fin;
    ofstream fout;
    int N, W;

    fin.open("input.txt");

    fin >> N;
    fin >> W;

    pair<int, int>* arr = new pair<int, int>[N];

    std::string s;
    //weight
    for (int i = 0; i < N; i++)
        fin >> arr[i].first;
    std::getline(fin, s); //read empty line
    //cost
    for (int i = 0; i < N; i++)
        fin >> arr[i].second;

    fin.close();

    int res = 0;
    solve(N, W, arr, res);

    fout.open("output.txt");
    fout << res;
    fout.close();

    delete[] arr;
    return 0;
}