/*У нас есть несколько предметов и рюкзак, который выдерживает вес C.
 * Предмет с номером i имеет вес xi. Определите число различных наборов предметов,
 * которые можно унести в рюкзаке. Два набора считаются различными,
 * если существует хотя бы один предмет, который включён в один из наборов и не включён в другой.

Входные данные
В первой строке ввода записано целое число n — количество предметов (1≤n≤30).
 Во второй строке записано n целых чисел xi (1≤xi≤109).
 В третье строке записано целое число C — вместимость рюкзака (0≤C≤109).

Выходные данные
Выведите единственное целое число — искомое число способов.*/

#include <iostream>
#include <vector>
#include <algorithm>

bool check (long long mask, int pos) {
    return (mask >> pos) & 1;
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<long long> firstHalf ((n / 2) + (n % 2));
    std::vector<long long> secondHalf ((n / 2));

    for (auto & i : firstHalf) {
        std::cin >> i;
    }

    for (auto & i : secondHalf) {
        std::cin >> i;
    }

    int c;
    std::cin >> c;

    int power;

    std::vector<long long> firstHalfSums;

    power = int(firstHalf.size());

    for (long long i = 0; i < 1 << power; ++ i) {
        long long res = 0;
        for (int j = 0; j < power; ++j) {
            if (check(i, j)) {
                res += firstHalf[j];
            }
        }
        if (res <= c) {
            firstHalfSums.push_back(res);
        }
    }

    std::vector<long long> secondHalfSums;

    power = int(secondHalf.size());

    for (long long i = 0; i < 1 << power; ++ i) {
        long long res = 0;
        for (int j = 0; j < power; ++j) {
            if (check(i, j)) {
                res += secondHalf[j];
            }
        }
        if (res <= c) {
            secondHalfSums.push_back(res);
        }
    }

    std::sort(secondHalfSums.begin(), secondHalfSums.end());

    long long res = 0;

    for (const auto & i : firstHalfSums) {
        res += std::upper_bound(secondHalfSums.begin(), secondHalfSums.end(), c - i)
                - secondHalfSums.begin();
    }

    std::cout << res;

}
