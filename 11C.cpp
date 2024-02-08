/*Дан массив чисел a1,…,an
. За одну операцию можно выбрать любые два соседних числа в массиве и заменить одно из них их наибольшим общим делителем.

Какое минимальное число операций необходимо, чтобы сделать все элементы массива равными 1
?

Входные данные
Первая строка содержит одно целое число n
 (1≤n≤2000
) — количество элементов в массиве.

Вторая строка содержит n
 целых чисел a1,a2,…,an
 (1≤ai≤109
) — элементы массива.

Выходные данные
Выведите -1, если невозможно сделать все элементы массива равными 1
. Иначе выведите минимальное число операций, необходимых для того, чтобы сделать все числа равными 1
.*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{

    long long n;
    std::cin >> n;

    std::vector<long long> values(n);

    int flag = 0;

    for (long long &i : values)
    {
        std::cin >> i;
        if (i == 1)
        {
            flag++;
        }
    }

    long long min_len = INT64_MAX;
    for (size_t l = 0; l < values.size(); l++)
    {
        if (flag)
        {
            break;
        }
        std::vector<long long> prefix_gcd(n - l);
        prefix_gcd[0] = values[l];

        for (size_t r = l + 1; r < values.size(); r++)
        {

            prefix_gcd[r - l] = std::__gcd(prefix_gcd[r - l - 1], values[r]);

            if (prefix_gcd[r - l] == 1)
            {

                if (r - l < min_len)
                {
                    min_len = r - l + 1;
                }

                break;
            }
        }
    }

    if (flag)
    {
        std::cout << n - flag << '\n';
    }
    else
    {
        if (min_len == INT64_MAX)
        {
            std::cout << -1 << '\n';
        }
        else
        {
            std::cout << min_len + n - 2 << '\n';
        }
    }
}
