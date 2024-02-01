/*Шреку необходимо пробраться в башню, чтобы спасти прекрасную принцессу Фиону. И сейчас его путь лежит через старый полуразвалившийся мост. 
Осёл очень боится упасть с этого моста в лавовую реку под ним и отказывается идти дальше, пока мост не будет полностью починен. 
Шрек не может идти без друга и решил отремонтировать его.

Мост представляет собой поле из n×m
 клеток, причем некоторые клетки ещё остались целыми. У Шрека есть только дощечки размера 1×2
 (которые можно поворачивать и получать 2×1
), установка которых занимает у него a
 секунд, и 1×1
, установка которых занимает b
 секунд. Ему необходимо закрыть все пустые клетки, причем только их, не накладывая дощечки друг на друга.

Определите, через какое минимальное количество секунд Шрек и Осёл смогут продолжить свой путь дальше.

Входные данные
Первая строка входного файла содержит 4 целых числа n
, m
, a
, b
 (1≤n,m≤100
, |a|≤1000
, |b|≤1000
). Каждая из последующих n
 строк содержит по m
 символов: символ  «.» (точка) обозначает целую клетку моста, а символ «*» (звёздочка) — пустую.

Выходные данные
В выходной файл выведите одно число — минимальное количество секунд, через которое наши герои смогут продолжить свой путь, закрыв пустые клетки моста (их и только их).*/

#include <iostream>
#include <vector>
#include <algorithm>

bool augment(int v, std::vector<std::vector<int>> &left_connections, std::vector<std::vector<int>> &right_connections, // NOLINT(misc-no-recursion)
             std::vector<bool> &used, std::vector<int> &match) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int i: left_connections[v]) {
        if (match[i] == -1) {
            match[i] = v;
            return true;
        }
        if (augment(match[i], left_connections, right_connections, used, match)) {
            match[i] = v;
            return true;
        }
    }
    return false;
}

int pair_count(std::vector<std::vector<int>> &left_connections, std::vector<std::vector<int>> &right_connections) {
    std::vector<bool> used(left_connections.size(), false);
    std::vector<bool> fill(left_connections.size(), false);
    std::vector<int> match(right_connections.size(), -1);
    int ans = 0;
    for (int i = 0; i < left_connections.size(); ++i) {
        if (augment(i, left_connections, right_connections, used, match)) {
            ans += 1;
            used = fill;
        }
    }
    return ans;
}

int main() {

    // declaration and input
    int height, width;
    std::cin >> height >> width;
    long long double_cost, single_cost;
    std::cin >> double_cost >> single_cost;
    std::vector<std::vector<bool>> bridge(height, std::vector<bool>(width, false));

    char input;
    int vertices = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cin >> input;
            while (input != '.' && input != '*') {
                std::cin >> input;
            }
            if (input == '*') {
                ++vertices;
                bridge[i][j] = true;
            }
        }
    }

    // building graph
    std::vector<std::vector<int>> left_connections(height * width / 2 + height * width % 2, std::vector<int>());
    std::vector<std::vector<int>> right_connections(height * width / 2, std::vector<int>());
    std::vector<int> neighbours;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            neighbours.clear();
            if (!bridge[i][j]) {
                continue;
            }
            if (i > 0 && bridge[i - 1][j]) {
                neighbours.push_back((((i - 1) * width) + j) / 2);
            }
            if (j > 0 && bridge[i][j - 1]) {
                neighbours.push_back(((i * width) + (j - 1)) / 2);
            }
            if (i < height - 1 && bridge[i + 1][j]) {
                neighbours.push_back((((i + 1) * width) + j) / 2);
            }
            if (j < width - 1 && bridge[i][j + 1]) {
                neighbours.push_back(((i * width) + (j + 1)) / 2);
            }
            if ((i + j) % 2 == 0) {
                left_connections[((i * width) + j) / 2] = neighbours;
            } else {
                right_connections[((i * width) + j) / 2] = neighbours;
            }
        }
    }

    // Kuhn's algorithm into output
    int pairs = pair_count(left_connections, right_connections);
//    std::cout << pairs;
    if (double_cost >= single_cost * 2) {
        std::cout << vertices * single_cost;
    } else {
        std::cout << (pairs * double_cost) + (vertices - (pairs * 2)) * single_cost;
    }

}
