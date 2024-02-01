/*Полный ориентированный взвешенный граф задан матрицей смежности. Постройте матрицу кратчайших путей между его вершинами. Гарантируется, что в графе нет циклов отрицательного веса.

Входные данные
В первой строке вводится единственное число N
 (1≤N≤100
) — количество вершин графа. В следующих N
 строках по N
 чисел задается матрица смежности графа (j
-е число в i
-й строке — вес ребра из вершины i
 в вершину j
). Все числа по модулю не превышают 100
. На главной диагонали матрицы — всегда нули.

Выходные данные
Выведите N
 строк по N
 чисел — матрицу расстояний между парами вершин, где j
-е число в i
-й строке равно весу кратчайшего пути из вершины i
 в j
.

*/

#include <iostream>
#include <vector>

void floyd(std::vector<std::vector<std::vector<int>>> &dp) {
    for (int i = 0; i < dp.size(); ++i) {
        dp[i][i][0] = 0;
    }
    for (int i = 1; i < dp.size(); ++i) { // layer
        for (int j = 0; j < dp.size(); ++j) { // start
            for (int k = 0; k < dp.size(); ++k) { // target
                int min_adjacent_cost = INT32_MAX;
                for (int l = 0; l < dp.size(); ++l) { // adjacent to target
                    if (l == k) {
                        continue;
                    }
                    if (min_adjacent_cost > dp[l][k][0] + dp[j][l][i - 1]) {
                        min_adjacent_cost = dp[l][k][0] + dp[j][l][i - 1];
                    }
                }
                dp[j][k][i] = std::min(dp[j][k][i - 1], min_adjacent_cost);
            }
        }
    }
}

int main() {

    int vertex_count;
    std::cin >> vertex_count;

    std::vector<std::vector<std::vector<int>>> dp(vertex_count, std::vector<std::vector<int>>(vertex_count,
                                                                                              std::vector<int>(
                                                                                                      vertex_count,
                                                                                                      INT32_MAX)));

    for (int i = 0; i < vertex_count; ++i) {
        for (int j = 0; j < vertex_count; ++j) {
            std::cin >> dp[i][j][0];
        }
    }

    floyd(dp);

    for (int i = 0; i < vertex_count; ++i) {
        for (int j = 0; j < vertex_count; ++j) {
            std::cout << dp[i][j][vertex_count - 1] << ' ';
        }
        std::cout << '\n';
    }

}
