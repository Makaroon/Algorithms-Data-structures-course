#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

/// Inspired by http://e-maxx.ru/algo/strong_connected_components

void dfs1(int curPos, vector<int>& order, vector<bool>& visited, vector<vector<bool>>& relations)
{
    visited[curPos] = true;
    for (int i = 0; i < relations.size(); ++i)
    {
        if (!visited[i] && relations[curPos][i])
            dfs1(i, order, visited, relations);
    }
    order.emplace_back(curPos);
}

void dfs2(int cur, vector<string>& comp, vector<bool>& visited, vector<string>& names, vector<vector<bool>>& relations)
{
    visited[cur] = true;
    comp.emplace_back(names[cur]);
    for (int i = 0; i < relations.size(); ++i)
    {
        if (!visited[i] && relations[i][cur])
            dfs2(i, comp, visited, names, relations);
    }
}


/// \param names - vector of actors
/// \param relations - vector of vectors of connections between actors
/// \return sorted groups of actors
vector<vector<string>> getList(vector<string>& names, vector<vector<bool>>& relations)
{
    vector<vector<string>> res;
    vector<bool> visited(relations.size(), false);
    vector<int> order;

    //first DFS to find cycles in the relationship graph
    for (int i = 0; i < relations.size(); ++i)
    {
        if (!visited[i])
            dfs1(i, order, visited, relations);
    }
    visited.assign(relations.size(), false);

    //Going from right to left so that the groups are sorted properly
    for (int i = relations.size() - 1; i >= 0; --i)
    {
        int v = order[i];
        if (!visited[v])
        {
            vector<string> comp;
            dfs2(v, comp, visited, names, relations);
            sort(comp.begin(), comp.end());
            res.emplace_back(comp);
        }
    }
    sort(res.begin(), res.end(), [](vector<string> l, vector<string> r) { return l.front() < r.front(); });
    return res;

}

int main()
{
    vector<string> names = vector<string>();
    vector<vector<bool>> relations;
    //int startIndex;

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

    vector<vector<string>> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[i].size(); j++)
            fout << res[i][j] << "\n";
        fout << "\n";
    }
    fout.close();

    return 0;
}