/*Компания Gnusmas разработала новую модель мобильного телефона.
 * Основное достоинство этой модели — ударопрочность: её корпус сделан из особого сплава,
 * и телефон должен выдерживать падение с большой высоты.

Компания Gnusmas арендовала n-этажное здание и наняла экспертов, чтобы те при помощи
 серии экспериментов выяснили, с какой высоты бросать телефон можно, а с какой — нельзя.
 Один эксперимент заключается в том, чтобы бросить телефон с какого-то этажа и посмотреть,
 сломается он от этого или нет. Известно, что любой телефон этой модели ломается, если его
 сбросить с x-го этажа или выше, где x — некоторое целое число от 1 до n, включительно, и не ломается,
 если сбросить его с более низкого этажа. Задача экспертов заключается в том, чтобы узнать число x и
 передать его рекламному отделу компании.

Задача осложняется тем, что экспертам предоставлено всего k образцов новой модели телефона.
 Каждый телефон можно бросать сколько угодно раз, пока он не сломается; после этого использовать
 его для экспериментов больше не удастся.

Подумав, эксперты решили действовать так, чтобы минимизировать максимально возможное количество
 экспериментов, которое может потребоваться произвести. Чему равно это количество?

Входные данные
В первой строке входного файла записаны через пробел два целых числа n и k — количество этажей в
 здании и количество предоставленных телефонов (1≤n≤100000, 0≤k<n).

Выходные данные
В выходной файл выведите единственное число — минимальное количество экспериментов, которое
 потребуется совершить, чтобы узнать число x и использовать не более k телефонов. Если решить
 задачу невозможно, выведите вместо этого −1.*/

#include <iostream>
#include <vector>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    --n; //read the thing incorrectly compared to original rules n should be lowered by 1
    if (k >= 17) {
        k = 17;
    } //just in case

    std::vector<int> dp ((n + 1) * (k + 1), 101101); // table of floors by phones, filled with answers
    for (int i = 0; i <= k; ++i) {
        dp[i * (n + 1)] = 0;
    }

    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
//            int min = 101101;
//            for (int s = 1; s <= j; ++s) {
//                if (std::max(dp[(i * (n + 1)) + j - s], dp[((i - 1) * (n + 1)) + s - 1]) < min) {
//                    min = std::max(dp[(i * (n + 1)) + j - s], dp[((i - 1) * (n + 1)) + s - 1]);
//                }
//            }
            int left = 1;
            int right = j;
            while (left < right - 1) {
                int mid = (right + left) / 2;
                if ((dp[(i * (n + 1)) + j - mid] - dp[((i - 1) * (n + 1)) + mid - 1]) > 0) {
                    left = mid;
                } else {
                    right = mid;
                }
            }
            dp[i * (n + 1) + j] = 1 +
                    std::min(std::max(dp[(i * (n + 1)) + j - left], dp[((i - 1) * (n + 1)) + left - 1]),
                             std::max(dp[(i * (n + 1)) + j - right], dp[((i - 1) * (n + 1)) + right - 1]));
        }
    }

    if (dp[(n + 1) * (k + 1) - 1] == 101101) {
        std::cout << -1;
    } else {
        std::cout << dp[(n + 1) * (k + 1) - 1];
    }

}
