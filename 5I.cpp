/*Даны две последовательности чисел — a и b.
 * Нужно найти наибольшую общую возрастающую подпоследовательность.
 * Более формально: такие 1≤i1<i2<⋯<ik≤a.n и 1≤j1<j2⋯<jk≤b.n, что ∀t:ait=bjt,ait<ait+1 и k максимально.

Входные данные
На первой строке целые числа n и m от 1 до 3000 — длины последовательностей.
 Вторая строка содержит n целых чисел, задающих первую последовательность.
 Третья строка содержит m целых чисел, задающих вторуя последовательность.
 Все элементы последовательностей — целые неотрицательные числа, не превосходящие 109.

Выходные данные
Выведите одно целое число — длину наибольшей общей возрастающей подпоследовательности.*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n1;
    std::cin >> n1;
    std::vector<long long> sequence1 (n1);

    int n2;
    std::cin >> n2;
    std::vector<long long> sequence2 (n2);

    for (auto & i : sequence1) {
        std::cin >> i;
    }

    for (auto & i : sequence2) {
        std::cin >> i;
    }

    std::vector<long long> dp ((n1 + 1) * (n2 + 1), 0);

    for (int i = 1; i <= n1; ++i) {

        long long tmp = 0;

        for (int j = 1; j <= n2; ++j) {

            // the confusing part

            if (sequence1[i - 1] > sequence2[j - 1]) {
                // it can be preceding to the seq1 element

                if (dp[(i - 1) * (n2 + 1) + j] > tmp) {
                    tmp = dp[(i - 1) * (n2 + 1) + j];
                }

            }

            // the recounting dp part

            long long modifier = -1; // so the " + 1 " has an effect only if the elements are matching

            if (sequence1[i - 1] == sequence2[j - 1]) {
                modifier = tmp;
            }

            dp[i * (n2 + 1) + j] = std::max(modifier + 1, dp[(i - 1) * (n2 + 1) + j]);

        }

    }

    long long ans = 0;

    for (int j = 1; j <= n2; ++j) {

        if (dp[n1 * (n2 + 1) + j] > ans) {
            ans = dp[n1 * (n2 + 1) + j];
        }

    }

    std::cout << ans;

}
