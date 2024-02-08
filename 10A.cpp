/*Найти все вхождения строки T
 в строку S
.

Входные данные
Первые две строки входных данных содержат строки S
 и T
, соответственно. Длины строк больше 0
 и меньше 50000
, строки содержат только строчные латинские буквы.

Выходные данные
Выведите номера символов, начиная с которых строка T
 входит в строку S
, в порядке возрастания.*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {

    std::string s, t, merged;
    std::cin >> s >> t;
    merged = t + '#' + s;

    std::vector<int> z_func_value(merged.length(), 0);
    int left = 0, right = 0;

    // ↓↓↓ code from https://neerc.ifmo.ru/wiki/index.php?title=Z-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F#.D0.AD.D1.84.D1.84.D0.B5.D0.BA.D1.82.D0.B8.D0.B2.D0.BD.D1.8B.D0.B9_.D0.B0.D0.BB.D0.B3.D0.BE.D1.80.D0.B8.D1.82.D0.BC_.D0.BF.D0.BE.D0.B8.D1.81.D0.BA.D0.B0
    for (int i = 1; i < merged.length(); i++)
    {  
        
        z_func_value[i] = std::max(0, std::min(right - i, z_func_value[i - left]));

        while ((i + z_func_value[i] < merged.size()) && (merged[z_func_value[i]] == merged[i + z_func_value[i]])) {
            z_func_value[i]++;
        }

        if (i + z_func_value[i] > right) {
            left = i;
            right = i + z_func_value[i];
        }

    }
    // ↑↑↑ code from https://neerc.ifmo.ru/wiki/index.php?title=Z-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F#.D0.AD.D1.84.D1.84.D0.B5.D0.BA.D1.82.D0.B8.D0.B2.D0.BD.D1.8B.D0.B9_.D0.B0.D0.BB.D0.B3.D0.BE.D1.80.D0.B8.D1.82.D0.BC_.D0.BF.D0.BE.D0.B8.D1.81.D0.BA.D0.B0

    
    for (int i = t.length() + 1; i < merged.length(); i++)
    {

        if (z_func_value[i] == t.length()) {
            std::cout << i - t.length() - 1 << ' ';
        }

    }

    std::cout << std::endl;

}
