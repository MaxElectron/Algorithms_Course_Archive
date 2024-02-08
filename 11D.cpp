/*Дан массив чисел a1,…,an
.

Найдите массив b1,…,bn
, такой что:

bi≥2
 для всех i
;
все элементы в нём попарно взаимно просты, то есть (bi,bj)=1
 для всех i≠j
;
b
 лексикографически не меньше a
;
b
 лексикографически минимален среди всех таких массивов.
Входные данные
Первая строка содержит одно целое число n
 (1≤n≤105)
 — число элементов в массивах a
 и b
.

Вторая строка содержит n
 целых чисел a1
, a2
, …
, an
 (2≤ai≤105)
 — элементы a
.

Выходные данные
Выведите n
 целых чисел, разделённых пробелами, i
-е из которых равно bi
.*/

#include <iostream>
#include <set>
#include <vector>

// the 200,000th prime is 2,750,159
const int MAX = 2750159;

[[nodiscard]] std::vector<int> lowest_prime_divisor() 
{
    int n = MAX;
    std::vector<int> lowest_prime_divisor (n + 1 , 0);
    std::vector<int> primes;
    for (size_t i = 2; i < lowest_prime_divisor.size(); i++)
    {
        if (!lowest_prime_divisor[i])
        {
            for (size_t j = i; j < lowest_prime_divisor.size(); j += i)
            {
                if (!lowest_prime_divisor[j]) {
                    lowest_prime_divisor[j] = i;
                }
            }
        }
    }

    return lowest_prime_divisor;
}

const std::vector<int> LPD = lowest_prime_divisor();

std::vector<int> factorize(int n, std::vector<int> &ans) 
{
    if (n == 1) {
        return ans;
    }
    if ((ans.empty()) || (ans[ans.size() - 1] != LPD[n])) {
        ans.push_back(LPD[n]);
    }
    factorize((n/(LPD[n])), ans);
    return ans;
}

int main()
{

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> values(n);

    for (int &i : values)
    {
        std::cin >> i;
    }

    std::set<int> available;
    
    for (int i = 1; i <= MAX; ++i)
    {
        available.insert(i);
    }

    bool flag = false;
    for (int i : values) {

        int current;
        // find lowest candidate available
        if (flag) {
            current = *available.lower_bound(2);
        } else {
            current = *available.lower_bound(i);
        }

        // check flag
        if (!flag && (current != i)) {
            flag = true;
        }

        // print it
        std::cout << current << ' ';

        // erase all with gcd > 1
        std::vector<int> factors;
        factorize(current, factors);
        for (int j : factors) {
            for (size_t k = j; k <= MAX; k+= j)
            {
                available.erase(k);
            }
        }
    }

    std::cout << std::endl;

}
