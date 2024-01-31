/*Дан массив a из n чисел. Нужно обрабатывать запросы:
0. set(i, x) – a[i] = x;
1. get(i, x) – найти min k : k > i и ak > x.
Формат входных данных
На первой строке длина массива n и количество запросов m. На второй строке n целых чисел –
массив a. Следующие m строк содержат запросы.
Индексы в массиве нумеруются с 1.
Запрос типа set: «0 i x».
Запрос типа get: «1 i x».
1 6 n, m 6 200 000.
1 6 i 6 n.
0 6 x, ai 6 200 000.
Формат выходных данных
На каждой запрос типа «get» на отдельной строке выведите k.
Если такого k не существует, выведите −1.*/

#include <iostream>
#include <vector>

class SegTree {
    
private:
    
    std::vector<int> data;
    const int NEUTRAL = INT32_MIN;
    
public:
    
    explicit SegTree(int size) {
        data.reserve(4 * size);
    }
    
    ~SegTree() = default;

    void build(const int base[], int left, int right, int val) {

        if (left == right) {
            data[val] = base[left];
            return;
        }

        int mid = (left + right) >> 1;
        build(base, left, mid, val * 2);
        build(base, mid + 1, right, 2 * val + 1);
        data[val] = std::max(data[2 * val], data[2 * val + 1]);

    }
    
    void recursiveUpdate(int indexCovered, int leftCovered, int rightCovered, int pos, int val) {

        if (leftCovered == rightCovered) {
            data[indexCovered] = val;
            return;
        }

        int mid = (leftCovered + rightCovered) >> 1;
        if (pos <= mid) {
            recursiveUpdate(indexCovered * 2, leftCovered, mid, pos, val);
        } else {
            recursiveUpdate(indexCovered * 2 + 1, mid + 1, rightCovered, pos, val);
        }
        data[indexCovered] = std::max(data[2 * indexCovered], data[2 * indexCovered + 1]);

    }
    
    int sum(int indexCovered, int leftCovered, int rightCovered, int left, int right) {

        if (left > right) {
            return NEUTRAL;
        }

        if (left == leftCovered && right == rightCovered) {
            return data[indexCovered];
        }

        int mid = (leftCovered + rightCovered) >> 1;
        return std::max(
                sum(2 * indexCovered, leftCovered, mid, left, std::min(right, mid)),
                sum(2 * indexCovered + 1, mid + 1, rightCovered, std::max(left, mid + 1), right)
        );

    }
    
};

int main() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int size, queries;
    std::cin >> size >> queries;

    int *base = new int[size];
    for (int i = 0; i < size; ++i) {
        std::cin >> base[i];
    }

    SegTree tree(size);
    tree.build(base, 0, size - 1, 1);

    int query, a, b;
    for (int i = 0; i < queries; ++i) {

        std::cin >> query >> a >> b;
        --a;

        if (query) {

            int l = a - 1, r = size - 1, mid;
            while (l + 1 < r) {
                mid = (l + r) / 2;
                if (tree.sum(1, 0, size - 1, a, mid) >= b) r = mid;
                else l = mid;
            }

            if (r == size - 1) {

                if (tree.sum(1, 0, size - 1, a, size - 1) >= b) {

                    std::cout << r + 1 << '\n';

                } else {

                    std::cout << "-1\n";

                }

            } else {

                std::cout << r + 1 << '\n';

            }

        } else {

            tree.recursiveUpdate(1, 0, size - 1, a, b);

        }
    }

    delete[] base;
    
}
