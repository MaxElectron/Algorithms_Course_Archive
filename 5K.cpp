/*Найдите максимальный вес золота, который можно унести в рюкзаке вместительностью S,
 * если есть N золотых слитков с заданными весами.

Входные данные
В первой строке входного файла запианы два числа — S и N (1⩽S⩽10000, 1⩽N⩽300).
 Далее следует N неотрицательных целых чисел, не превосходящих 100 000 — веса слитков.

Выходные данные
Выведите искомый максимальный вес.

*/

#include <iostream>
#include <vector>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int capacity, n;
    std::cin >> capacity >> n;
    std::vector<int> weighs (n, 0);
    std::vector<int> dp ((n + 1) * (capacity + 1), 0); // answer for first i items and capacity of j

    for (int & i : weighs) {
        std::cin >> i;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= capacity; ++j) {

            if ((j - weighs[i - 1]) < 0) {
                dp[i * (capacity + 1) + j] = dp[(i - 1) * (capacity + 1) + j];
                continue;
            }

            dp[i * (capacity + 1) + j] = std::max(dp[(i - 1) * (capacity + 1) + j],
                                                  dp[(i - 1) * (capacity + 1) + j - weighs[i - 1]] + weighs[i - 1]);

        }
    }

    std::cout << dp[(n + 1) * (capacity + 1) - 1];

}
