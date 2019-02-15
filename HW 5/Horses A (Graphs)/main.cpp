#include "ReadWriter.cpp"
#include <queue>
#include <algorithm>

//Можно добавлять любые методы для решения задачи.

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node>& graph, int start, std::vector<std::string>& result)
{
    //TODO
    result.push_back(graph[start].name);
    graph[start].visited = true;
    std::queue<Node*> temp;
    std::vector<Node*> unsortedCh;
    std::vector<std::string> unsChS;

    Node* curNode = &graph[start];
    temp.push(curNode);

    //temp - очередь, в которую помещаются пройденные элементы
    //если temp опустел - обзод в ширину можно считать завершенным
    while (!temp.empty())
    {
        for (int i = 0; i < result.size(); ++i)
        {
            while (!temp.empty())
            {
                curNode = temp.front();
                temp.pop();
                for (Node* nbh : curNode->neighbours)
                {
                    if (!nbh->visited)
                    {
                        // все не пройденные соседи сначала помещаются в контейнер неотсортированных имен,
                        // где сортируются и кладутся в общую очередь
                        nbh->visited = true;
                        unsortedCh.push_back(nbh);
                        unsChS.push_back(nbh->name);
                    }
                }
            }
            //сортровка и перемещение соседей из отдельного контейнера в общую очередь
            std::sort(unsChS.begin(), unsChS.end());
            for (int j = 0; j < unsortedCh.size(); ++j)
            {
                temp.push(unsortedCh[j]);
                result.push_back(unsChS[j]);
            }
            unsortedCh.clear();
            unsChS.clear();
        }
    }
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
