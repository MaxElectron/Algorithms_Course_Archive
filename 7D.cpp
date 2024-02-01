/*Дан ориентированный невзвешенный граф. Необходимо его топологически отсортировать.

Входные данные
В первой строке входного файла даны два натуральных числа N
 и M
 (1≤N≤100000,M≤100000
) — количество вершин и рёбер в графе соответственно. Далее в M
 строках перечислены рёбра графа. Каждое ребро задаётся парой чисел — номерами начальной и конечной вершин соответственно.

Выходные данные
Вывести любую топологическую сортировку графа в виде последовательности номеров вершин. Если граф невозможно топологически отсортировать, вывести -1.*/

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
            if (color[to] == 1) { // grey
                flag = true;
            }
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
    std::vector<std::vector<int>> graph (vertexCount);

    int edgeStart;
    int edgeEnd;
    for (int i = 0; i < edgeCount; ++i) {
        std::cin >> edgeStart;
        std::cin >> edgeEnd;
        graph[edgeStart - 1].push_back(edgeEnd - 1);
    }

    bool flag = false;
    int timer = 0;
    std::vector<int> tin(vertexCount, 0);
    std::vector<int> tout(vertexCount, 0);
    std::vector<int> parent(vertexCount, -1);
    std::vector<int> color(vertexCount, 0); // 0 = white; 1 = grey; 2 = black;

    for (int i = 0; i < vertexCount; ++i) {
        if (color[i] == 0) { // white
            dfs(graph, flag, i, -1, timer, tin, tout, parent, color);
        }
    }

    if (flag) {

        std::cout << -1;
        return 0;

    } else {

        std::map<int, int> dict;

        for (int i = 0; i < tout.size(); ++i) {
            dict[tout[i]] = i;
        }

        std::sort(tout.begin(), tout.end());

        std::reverse(tout.begin(), tout.end());

        for (int i : tout) {
            std::cout << dict[i] + 1 << ' ';
        }
        std::cout << '\n';

    }

}
