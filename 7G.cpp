/*Вам задан неориентированный граф с N
 вершинами и M
 ребрами. В графе отсутствуют петли и кратные ребра.

Определите компоненты связности заданного графа.

Входные данные
Граф задан во входном файле следующим образом: первая строка содержит числа N
 и M (1≤N≤20000,1≤M≤200000)
. Каждая из следующих M
 строк содержит описание ребра — два целых числа из диапазона от 1
 до N
 — номера концов ребра.

Выходные данные
На первой строке выходного файла выведите число L
 — количество компонент связности заданного графа. На следующей строке выведите N
 чисел из диапазона от 1
 до L
 — номера компонент связности, которым принадлежат соответствующие вершины. Компоненты связности следует занумеровать от 1
 до L
 произвольным образом.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

void dfs(std::vector<std::vector<int>> &graph, bool &flag, // NOLINT(misc-no-recursion)
         int vertex, int parentOf, int &timer, std::vector<int> &tin, std::vector<int> &tout,
         std::vector<int> &parent, std::vector<int> &color) {
    tin[vertex] = timer++;
    parent[vertex] = parentOf;
    color[vertex] = 1; // grey
    for (int to: graph[vertex]) {

        if (color[to] != 0) { // white
            continue;
        }

        dfs(graph, flag, to, vertex, timer, tin, tout, parent, color);

    }

    tout[vertex] = timer++;
    color[vertex] = 2; // black

}

int main() {

    int edgeCount;
    int vertexCount;
    std::cin >> vertexCount >> edgeCount;
    std::vector<std::vector<int>> graph(vertexCount);

    int edgeStart;
    int edgeEnd;
    for (int i = 0; i < edgeCount; ++i) {
        std::cin >> edgeStart;
        std::cin >> edgeEnd;
        graph[edgeStart - 1].push_back(edgeEnd - 1);
        graph[edgeEnd - 1].push_back(edgeStart - 1);
    }

    bool flag = false;
    int timer = 0;
    std::vector<int> timestamps;
    std::vector<int> tin(vertexCount, 0);
    std::vector<int> tout(vertexCount, 0);
    std::vector<int> parent(vertexCount, -1);
    std::vector<int> color(vertexCount, 0); // 0 = white; 1 = grey; 2 = black;

    for (int i = 0; i < vertexCount; ++i) {
        if (color[i] == 0) { // white
            dfs(graph, flag, i, -1, timer, tin, tout, parent, color);
            timestamps.push_back(timer++);
        }
    }

    std::map<int, int> dict;

    for (int i = 0; i < tout.size(); ++i) {
        dict[tout[i]] = i;
    }

    std::sort(tout.begin(), tout.end());

    std::vector<int> ans(vertexCount, 0);

    int counter = 1;

    for (int i: tout) {
        while (i >= timestamps[counter - 1]) { // or just >
            ++counter;
        }
        ans[dict[i]] = counter;
    }

    std::cout << counter << '\n';

    for (int i: ans) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

}
