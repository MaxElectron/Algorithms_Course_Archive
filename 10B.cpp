/*Привидение Петя любит играть со своими кубиками. Он любит выкладывать их в ряд и разглядывать свое творение. Однако недавно друзья решили подшутить над Петей и поставили в его игровой комнате зеркало. Ведь всем известно, что привидения не отражаются в зеркале! А кубики отражаются. Теперь Петя видит перед собой N
 цветных кубиков, но не знает, какие из этих кубиков настоящие, а какие — всего лишь отражение в зеркале. Помогите Пете! Выясните, сколько кубиков может быть у Пети. Петя видит отражение всех кубиков в зеркале и часть кубиков, которая находится перед ним. Часть кубиков может быть позади Пети, их он не видит.


Входные данные
Первая строка входного файла содержит число N
 (1≤N≤106
) и количество различных цветов, в которые могут быть раскрашены кубики — M
 (1≤M≤106
). Следующая строка содержит N
 целых чисел от 1 до M
 — цвета кубиков.

Выходные данные
Выведите в выходной файл все такие K
, что у Пети может быть K
 кубиков в подрядке возрастания*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {

    // declaration begining
    int n, m;
    std::cin >> n >> m; 
    // n - cubes, m - colors

    std::vector<int> cubes (n * 2 + 1), z_func_value (n * 2 + 1, 0);

    for (int i = 0; i < n; i++)
    {
        std::cin >> cubes[i];
        cubes[n * 2 - i] = cubes[i];
    }
    cubes[n] = 0;

    int left = 0, right = 0;
    // declaration end

    // execution begining
    // ↓↓↓ code from https://neerc.ifmo.ru/wiki/index.php?title=Z-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F#.D0.AD.D1.84.D1.84.D0.B5.D0.BA.D1.82.D0.B8.D0.B2.D0.BD.D1.8B.D0.B9_.D0.B0.D0.BB.D0.B3.D0.BE.D1.80.D0.B8.D1.82.D0.BC_.D0.BF.D0.BE.D0.B8.D1.81.D0.BA.D0.B0
    for (int i = 1; i < cubes.size(); i++)
    {
        z_func_value[i] = std::max(0, std::min(right - i, z_func_value[i - left]));

        while ((i + z_func_value[i] < cubes.size()) && (cubes[z_func_value[i]] == cubes[i + z_func_value[i]])) {
            z_func_value[i]++;
        }

        if (i + z_func_value[i] > right) {
            left = i;
            right = i + z_func_value[i];
        }
    }
    // ↑↑↑ code from https://neerc.ifmo.ru/wiki/index.php?title=Z-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F#.D0.AD.D1.84.D1.84.D0.B5.D0.BA.D1.82.D0.B8.D0.B2.D0.BD.D1.8B.D0.B9_.D0.B0.D0.BB.D0.B3.D0.BE.D1.80.D0.B8.D1.82.D0.BC_.D0.BF.D0.BE.D0.B8.D1.81.D0.BA.D0.B0
    // execution end

    // output
    for (int i = n + 1; i < z_func_value.size(); i++)
    {
        if (z_func_value[i] == z_func_value.size() - i) {
            if (z_func_value[i] % 2 == 0) {
                std::cout << n - (z_func_value[i] / 2) << ' ';
            }   
        }
    }
    std::cout << n << std::endl;

}
