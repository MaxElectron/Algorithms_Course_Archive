/*Даны n
 отрезков на прямой. Пара отрезков называются вложенной, если отрезки не совпадают, и один отрезок содержит второй. Посчитать количество пар вложенных отрезков.

Входные данные
Целоы число n
 (1≤n≤300000
) и n
 пар целых чисел 0≤li≤ri≤109
.

Выходные данные
Одно число – количество пар вложенных отрезков.*/

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T, class Arithmetic>
class [[maybe_unused]] Fenwick {
private:

    std::vector<T> data;
    Arithmetic foo;

public:

    [[maybe_unused]] explicit Fenwick(std::vector<T> base);

    [[maybe_unused]] void change(long long index, T value);

    [[maybe_unused]] [[maybe_unused]] void set(long long index, T value);

    [[maybe_unused]] T sum(long long index);

    [[maybe_unused]] T sum(long long left, long long right); // []

};

template<typename T, class Arithmetic>
[[maybe_unused]] Fenwick<T, Arithmetic>::Fenwick(std::vector<T> base) {
    data = std::vector<T> (base.size(), foo.neutral());
//    for (long long i = 0; i < base.size(); ++i) {
//        change(i, base[i]);
//    }
}

template<typename T, class Arithmetic>
[[maybe_unused]] void Fenwick<T, Arithmetic>::change(long long index, T value) {
    while (index < data.size()) {
        data[index] = foo(data[index], value);
        index |= index + 1;
    }
}

template<typename T, class Arithmetic>
[[maybe_unused]] void Fenwick<T, Arithmetic>::set(long long index, T value) {
    change(index, foo(value, foo.opposite(sum(index, index))));
}

template<typename T, class Arithmetic>
[[maybe_unused]] T Fenwick<T, Arithmetic>::sum(long long index) {
    T ans = foo.neutral();
    while (index >= 0) {
        ans = foo(ans, data[index]);
        index = (index & (index + 1)) - 1;
    }
    return ans;
}

template<typename T, class Arithmetic>
[[maybe_unused]] T Fenwick<T, Arithmetic>::sum(long long left, long long right) {
    if (left > right) {
        return foo.neutral();
    }
    if (left == 0) {
        return sum(right);
    }
    return foo(sum(right), foo.opposite(sum(left - 1)));
}

template <typename T>
class Digits {
public:
    T operator() (T a, T b) {
        return a + b;
    }

    T neutral () {
        return 0;
    }

    T opposite (T a) {
        return -a;
    }
};

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int amount;
    std::cin >> amount;

    std::vector<std::pair<long long, long long>> segments (amount);
    int l, r;
    for (int i = 0; i < amount; ++i) {
        std::cin >> l >> r;
        segments[i] = std::pair<long long, long long>{l, r};
    }

    std::sort(segments.begin(), segments.end(), []
            (const std::pair<long long, long long>& a, const std::pair<long long, long long>& b) {
        if ((a.second > b.second) || ((a.second == b.second) && (a.first < b.first))) {
            return true;
        }
        return false;
    });

    int n = amount;
    std::vector<std::pair<int, int>> pairs(n);
    for(int i = 0; i < n; ++i) {
        pairs[i] = {segments[i].first, i};
    }
    sort(pairs.begin(), pairs.end());
    int next = 0;
    for (int i = 0; i < n; ++i) {
        if(i > 0 && pairs[i-1].first != pairs[i].first) {
            next++;
        }
        segments[pairs[i].second].first = next;
    }

    std::vector<long long> leftEndsCompressedAmounts (next + 1, 0);
    Fenwick<long long, Digits<long long>> tree (leftEndsCompressedAmounts);

    long long ans = 0;
    long long streak = 0;

    for (long long i = 0; i < amount; ++i) {
        if (i != 0) {
            if ((segments[i].first != segments[i - 1].first) || (segments[i].second != segments[i - 1].second)) {
                streak = 0;
            }
        }
        ans += tree.sum(segments[i].first);
        ans -= streak;
        tree.change(segments[i].first , 1);
        ++streak;
    }
    
    std::cout << ans << '\n';
}
