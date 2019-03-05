#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void dfs(int cur, vector<vector<bool>>& relations, vector<bool>& used, vector<string>& names, vector<string>& res)
{
    used[cur] = true;
    vector<int> after;
    for (int i = 0; i < relations.size(); ++i)
    {
        if (relations[cur][i])
            after.emplace_back(i);
    }
    sort(after.begin(), after.end(), [&names](int l, int r) { return names[l] < names[r]; });
    for (int& i : after)
    {
        if (!used[i])
            dfs(i, relations, used, names, res);
    }
    res.emplace_back(names[cur]);
}

vector<string> getList(vector<string>& names, vector<vector<bool>>& relations)
{
    vector<string> res;
    vector<bool> used(relations.size(), false);
    vector<int> sources(relations.size());

    vector<bool> isSource(relations.size(), false);
    for (int i = 0; i < names.size(); i++)
    {
        for (int j = 0; j < names.size(); j++)
        {
            if (relations[j][i])
                isSource[i] = true;
        }
        if (!isSource[i])
            sources.push_back(i);
    }
    sort(sources.begin(), sources.end(), [&names](int l, int r) { return names[l] < names[r]; });
    for (int& i : sources)
    {
        if (!used[i])
            dfs(i, relations, used, names, res);
    }
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    vector<string> names = vector<string>();
    vector<vector<bool>> relations;
//    int startIndex;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        string str = "";
        getline(fin, str);

        while (str != "#")
        {
            names.emplace_back(str.substr(str.find(' ') + 1));
            getline(fin, str);
        }

        relations = vector<vector<bool>>(names.size());

        for (int i = 0; i < names.size(); i++)
        {
            relations[i] = vector<bool>(names.size());
            for (int j = 0; j < names.size(); j++)
                relations[i][j] = false;
        }

        getline(fin, str);

        while (fin)
        {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            getline(fin, str);
        }

        fin.close();
    }

    vector<string> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
        fout << res[i] << "\n";
    fout.close();

    return 0;
}