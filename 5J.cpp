/*Дана последовательность целых чисел длины n.
 * Нужно найти количество различных непустых подпоследовательностей.

Входные данные
На первой строке n (n≤3⋅105). На второй строке n
 положительных целых чисел, каждое из которых не превосходит 106.

Выходные данные
Количество различных подпоследовательностей по модулю 109+7.*/

#include <iostream>
#include <vector>
#include <map>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    const long long MOD = 1000000007;

    int n;
    std::map<int, long long> previous;
    std::cin >> n;
    std::vector<int> seq (n);
    std::vector<long long> dp (n + 1, 0); // answer for prefix of length n

    for (int & i : seq) {
        std::cin >> i;
    }

    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {

        long long delta = previous[seq[i - 1]];

        previous[seq[i - 1]] = dp[i - 1];

//        for (int j = i - 2; j >= 0; --j) {
//
//            if (seq[j] == seq[i - 1]) {
//                delta = dp[j];
//                break;
//            }
//
//        }

        dp[i] = ((dp[i - 1] * 2) - delta) % MOD;

    }

    if (dp[n] < 0) {
        dp[n] += MOD;
    }

    std::cout << dp[n] - 1;
}
