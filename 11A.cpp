/*Заданы четыре целых числа a
, b
, c
, d
 (1≤|a|,|b|,|c|,|d|≤109
). Вычислите ad+bcbdmod(109+7)
.

Входные данные
Первая строка входного файла содержит четыре целых числа a
, b
, c
 и d
.

Выходные данные
Выведите одно целое число — ответ к задаче.*/

#include <iostream>

const long long MOD = 1000000007;

// code for gcd from https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
long long gcd(long long a, long long b, long long &x, long long &y)
{
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    long long x_r, y_r;

    long long res = gcd(b % a, a, x_r, y_r);
    x = y_r - (b / a) * x_r;
    y = x_r;

    return res;
}

long long inverse(long long value)
{
    long long x, y;
    gcd((value % MOD + MOD) % MOD, MOD, x, y);
    return (x % MOD + MOD) % MOD;
}

int main()
{

    long long a, b, c, d;
    std::cin >> a >> b >> c >> d;

    std::cout << ((((((a * d) % MOD) + ((b * c) % MOD)) % MOD) * inverse(b * d)) % MOD + MOD) % MOD << '\n' ;
    
}
