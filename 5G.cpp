/*Даны две последовательности. 
 * Найдите длину их наибольшей общей подпоследовательности (подпоследовательность — это то, 
 * что можно получить из данной последовательности вычеркиванием некоторых элементов).

Входные данные
В первой строке входного файла записано число N — длина первой последовательности (1⩽N⩽1000). 
 Во второй строке записаны члены первой последовательности (через пробел) — 
 целые числа, не превосходящие 10 000 по модулю. 
 В третьей строке записано число M — длина второй последовательности (1⩽M⩽1000). 
 В четвертой строке записаны члены второй последовательности (через пробел) — 
 целые числа, не превосходящие 10 000 по модулю.

Выходные данные
В выходной файл требуется вывести единственное целое число: длину наибольшей общей подпоследовательности, 
 или число 0, если такой не существует.*/

#include <iostream>
#include <vector>

int lcs (int n1, int n2, const std::vector<int> & sequence1, const std::vector<int> & sequence2) {

    //in dp we will store the table of answer for prefixes of matching size
    std::vector<int> dp ((n1 + 1) * (n2 + 1), 0);
    //the largest subsequence of prefix size 0 and something is 0


    //recalc by consequtive incrementation of the prefix sizes

    //we either add one symbol if it mathes corresponding one in the other sequence or take the answer for the lesser
    //size without change (select the optimal one each time)

    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {

            int a = 0;

            if (sequence1[i - 1] == sequence2[j - 1]) {
                a = 1;
            }

            dp[i * (n2 + 1) + j] = std::max(dp[(i - 1) * (n2 + 1) + j],
                                            std::max(dp[(i - 1) * (n2 + 1) + j - 1] + a, dp[i * (n2 + 1) + j - 1]));

        }
    }

    //answer for the prefixes the size of the whole sequences is the answer for whole sequences
    return dp[(n1 + 1) * (n2 + 1) - 1];
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n1;
    std::cin >> n1;
    std::vector<int> sequence1 (n1);

    for (int & i : sequence1) {
        std::cin >> i;
    }

    int n2;
    std::cin >> n2;
    std::vector<int> sequence2 (n2);

    for (int & i : sequence2) {
        std::cin >> i;
    }

    int ans;

    ans = lcs(n1, n2, sequence1, sequence2);

    std::cout << ans;

}
