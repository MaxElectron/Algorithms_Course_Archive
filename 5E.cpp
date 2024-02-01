/*Группа математиков проводит бои между натуральными числами.
 * Результаты боя между двумя натуральными числами, вообще говоря,
 * случайны, однако подчиняются следующему правилу: если одно из чисел
 * не менее чем в два раза превосходит другое, то большее число всегда
 * побеждает; в противном случае победить может как одно, так и другое число.

Бой называется неинтересным, если его результат предопределён.
 Множество натуральных чисел называется мирным, если бой любой
 пары различных чисел из этого множества неинтересен.
 Силой множества называется сумма чисел в нём. Сколько
 существует мирных множеств натуральных чисел силы n?

Входные данные
В первой строке входного файла задано число n (1≤n≤2000).

Выходные данные
В первой строке выходного файла выведите одно число —
 количество мирных множеств натуральных чисел силы n.*/


#include <iostream>
#include <vector>

long long findPeace(int n) {

    std::vector<long long> dp ((n + 1) * (n + 1), 0);
    // in dp we will store how many sets of given power have given element as the maximal element (in n by n table),
    // for sets of power 0 the answer is 0, and for ways to select power of 0 for the non-0 max element is also zero,
    // the 0 out of 0 case has value of 1, but we account for it here*, so we make it 0 as well


    // recount by incrementing both parameters of the dp

    // we can add the said element to an existing set and get the given power if we take the set of power lowered by
    // the value of the said element and take only those from the previous selection where the greatest element is at
    // least twice as small, and add together the amounts of given sets to get the amount of the sets we are
    // trying to recalculate

    for (int i = 1; i <= n; ++i) {

        for (int j = i / 2; j < i; ++j) {

            long long sum = 0;

            for (int k = 1; k <= j / 2; ++k) {
                sum += dp[(i - j) * (n + 1) + k];
            }

            dp[i * (n + 1) + j] = sum;

        }

        dp[i * (n + 1) + i] = 1; //here*

    } // by power

    long long ans = 0;

    // the answer is the sum of amounts of all the possible sets of given power (iterated by the max element)
    for (int i = 0; i <= n; ++i) {
        ans += dp[n * (n + 1) + i];
    }

    return ans;

}

int main() {

    int n;
    std::cin >> n;

    long long ans;

    ans = findPeace(n);

    std::cout << ans;

}
