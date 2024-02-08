/*Задано целое число N
 (4≤N≤106)
. Найти сумму наименьших простых делителей всех составных чисел, больших 2 и не превосходящих N
.

Входные данные
Первая строка входных данных содержит одно целое число N
.

Выходные данные
Выведите одно целое число — ответ к задаче.*/

#include <algorithm>
#include <iostream>
#include <vector>

void compute(std::vector<int> &lowest_prime_devisor)
{
    for (size_t i = 2; i < lowest_prime_devisor.size(); i++)
    {
        if (!lowest_prime_devisor[i])
        {
            for (size_t j = i * 2; j < lowest_prime_devisor.size(); j += i)
            {
                if (!lowest_prime_devisor[j]) {
                    lowest_prime_devisor[j] = i;
                }
            }
        }
    }
}

int main()
{

    int n;
    std::cin >> n;
    std::vector<int> lowest_prime_devisor(n + 1, 0);

    lowest_prime_devisor[1] = 1;
    compute(lowest_prime_devisor);

    long long sum = 0;
    for (size_t i = 2; i < lowest_prime_devisor.size(); i++)
    {
        sum += lowest_prime_devisor[i];
    }

    std::cout << sum << '\n';
}
