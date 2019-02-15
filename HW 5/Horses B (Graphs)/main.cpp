#include "ReadWriter.cpp"
#include <queue>
#include <algorithm>

//Можно добавлять любые методы для решения задачи.

//Метод сравнения для сортировку в алфавитном порядке
bool comp(Node* a, Node* b)
{
    return a->name < b->name;
}

//рекурсивный метод "перекраски" поиска в глубину
void dfs(Node* nd, std::vector<std::string>& result)
{
    result.push_back(nd->name);
    nd->visited = true;
    //так как список по алфавиту - необходимо сперва его отсортировать
    std::sort(nd->neighbours.begin(), nd->neighbours.end(), comp);
    for (Node* n : nd->neighbours)
    {
        if (!n->visited)
            dfs(n, result);
    }
}


//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node>& graph, int start, std::vector<std::string>& result)
{
    //TODO
    Node* curNode = &graph[start];
    dfs(curNode,result);
}

int main()
{
    std::vector<Node> graph;
    std::vector<std::string> result;
    int start;

    ReadWriter rw;
    rw.readGraph(graph, start);
    solve(graph, start, result);
    rw.writeAnswer(result);
    return 0;
}
