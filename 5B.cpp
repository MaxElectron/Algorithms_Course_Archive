/*Вам требуется написать программу, которая по заданной последовательности находит максимальную
 * невозрастающую её подпоследовательность (т.е такую последовательность чисел ai1,ai2,…,aik (i1<i2<…<ik),
 * что ai1≥ai2≥…≥aik и не существует последовательности с теми же свойствами длиной k+1).

Входные данные
В первой строке задано число n — количество элементов последовательности (1≤n≤239017). В последующих строках
 идут сами числа последовательности ai, отделенные друг от друга произвольным количеством пробелов и
 переводов строки (все числа не превосходят по модулю 231−2).

Выходные данные
Вам необходимо выдать в первой строке выходного файла число k — длину максимальной невозрастающей
 подпоследовательности. В последующих строках должны быть выведены (по одному числу в каждой строке)
 все номера элементов исходной последовательности ij, образующих искомую подпоследовательность. Номера
 выводятся в порядке возрастания. Если оптимальных решений несколько, разрешается выводить любое.*/


#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> findAscendingSubsequence (int n, const std::vector<int> & values) {

    std::vector<int> output;

    // in the dp we will store what's the smallest number in which sequence of the matching length could end
    std::vector<int> dp (n, INT32_MAX);
    // default values are neutral element relative to upper_bound function,
    // as the value that will be overshadowed by any other

    // here we store which index the value in dp has inside values;
    std::vector<int> dpCorrespondingIndexes (n, -1);

    // here we store the presceding element index to the corresponding element in values
    std::vector<int> valuesCorrespondingIndexes (n, -1);

    // put them in reverse order, so we search for ascending subsequence and then just output it backwards

    // recalc by incrementation of length of the prefix

    // we will go through the elements of values, finding the first place in the tracebeck array where we can put it,
    // then will memorize the corresponding index (for more complete explanation refer to the lecture, where said
    // solution was prooved to be working)

    for (int i = 0; i < n; ++i) {
        // find the first position in dp which is greater than the value and replace it respectively
        int index = int(std::upper_bound(dp.begin(), dp.end(), values[i]) - dp.begin());
        dp[index] = values[i];
        dpCorrespondingIndexes[index] = i;
        if (index > 0) {
            valuesCorrespondingIndexes[i] = dpCorrespondingIndexes[index - 1];
        }
    }

    // the largest ascending subsequence length
    int ans = int(std::lower_bound(dp.begin(), dp.end(), INT32_MAX) - dp.begin());

    int index = dpCorrespondingIndexes[ans - 1];

    // here we trace back the subsequence from the furthest corner of dp,
    // as that's the cell of answer for whole sequences, and the size will be the size of the recovered subsequence
    while (index != -1) {
        output.push_back(n - index);
        index = valuesCorrespondingIndexes[index];
    }

//    std::reverse(output.begin(), output.end());

    return output;
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> values (n);

    std::vector<int> ans;

    for (int i = n - 1; i >= 0; --i) {
        std::cin >> values[i];
    }

    ans = findAscendingSubsequence(n, values);

    std::cout << ans.size() << '\n';

    for (auto i : ans) {
        std::cout << i << ' ';
    }

    std::cout << '\n';

}
