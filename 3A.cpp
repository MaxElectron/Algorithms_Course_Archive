/*В начальный момент времени последовательность an
 задана следующей формулой: an=(n2mod12345)+(n3mod23456)
. Требуется много раз отвечать на запросы следующего вида:

Найти разность между максимальным и минимальным значениями среди элементов ai,ai+1,…,aj
.
Присвоить элементу ai
 значение j
.
Входные данные
Первая строка входного файла содержит натуральное число k
 — количество запросов (1≤k≤100000
). Следующие k
 строк содержат запросы, по одному на строке. Запрос номер i
 описывается двумя целыми числами xi
, yi
.

Если xi>0
, то требуется найти разность между максимальным и минимальным значениями среди элементов axi,…,ayi
. При этом 1≤xi≤yi≤100000
.

Если xi<0
, то требуется присвоить элементу a|xi|
 значение yi
. В этом случае −100000≤xi≤−1
 и |yi|≤100000
.

Выходные данные
Для каждого запроса первого типа в выходной файл требуется вывести одну строку, содержащую разность между максимальным и минимальным значениями на соответствующем отрезке.*/

#include <iostream>
#include <vector>

template <class T, class BinaryFunctionContainer>
class [[maybe_unused]] SegmentTree {
private:

    std::vector<T> data;
    BinaryFunctionContainer foo;
    size_t depth;

    T recursiveRequest(size_t coveringIndex, size_t leftCovered, size_t rightCovered, size_t left, size_t right);
    void recursiveUpdate(size_t coveringIndex, size_t leftCovered, size_t rightCovered, size_t pos, size_t val);

public:

    [[maybe_unused]] explicit SegmentTree(std::vector<T> base);

    [[maybe_unused]] T request(size_t left, size_t right);

    [[maybe_unused]] void update(size_t pos, T val);

};

template<class T, class BinaryFunctionContainer>
T SegmentTree<T, BinaryFunctionContainer>::recursiveRequest(
        size_t coveringIndex,
        size_t leftCovered,
        size_t rightCovered,
        size_t left,
        size_t right) {

    if (leftCovered > right || rightCovered < left){
        return foo.neutral();
    }
    if (left <= leftCovered && rightCovered <= right){
        return data[coveringIndex];
    }
    size_t mid = (leftCovered + rightCovered) / 2;
    return foo(recursiveRequest(coveringIndex* 2 + 1, leftCovered, mid, left, right),
               recursiveRequest(coveringIndex* 2 + 2, mid + 1, rightCovered, left, right));
} // OK

template<class T, class BinaryFunctionContainer>
void SegmentTree<T, BinaryFunctionContainer>::recursiveUpdate(
        size_t coveringIndex,
        size_t leftCovered,
        size_t rightCovered,
        size_t pos,
        size_t val) {
    if (leftCovered == rightCovered){
        data[coveringIndex] = val;
    }
    else {
        size_t mid = (leftCovered + rightCovered) / 2;
        if (pos <= mid){
            recursiveUpdate(coveringIndex * 2 + 1, leftCovered, mid, pos, val);
        }
        else {
            recursiveUpdate(coveringIndex * 2 + 2, mid + 1, rightCovered, pos, val);
        }
        data[coveringIndex] = foo(data[coveringIndex * 2 + 1], data[coveringIndex * 2 + 2]);
    }
} // OK

template<class T, class BinaryFunctionContainer>
[[maybe_unused]] SegmentTree<T, BinaryFunctionContainer>::SegmentTree(std::vector<T> baseData) {

    // count depth
    size_t count = 0;
    size_t n = baseData.size();

    // first n in the below condition
    // is for the case where n is 0
    if (n && !(n & (n - 1))) {
        depth = n;
    } else {
        while( n != 0)
        {
            n >>= 1;
            count += 1;
        }

        depth = count + 1;
    }

    // resize data and fill the base and the blank space
    data.resize(1 << depth);
    for (size_t i = (1 << (depth - 1)); i < (1 << depth); ++i) {
        if (i - (1 << (depth - 1)) < baseData.size()) {
            data[i] = baseData[i - (1 << (depth - 1))];
        } else {
            data[i] = foo.neutral();
        }
    }

    // build up
    for (size_t i = (1 << (depth - 1)) - 1; i >= 0; --i) {
        data[i] = foo(data[2 * i + 1], data[2 * i + 2]);
        if (i == 0) break;
    }

} // OK

template<class T, class BinaryFunctionContainer>
[[maybe_unused]] T SegmentTree<T, BinaryFunctionContainer>::request(size_t left, size_t right) {
    return recursiveRequest(0, 0, (1 << (depth - 1)) - 1, left, right);
} // OK

template<class T, class BinaryFunctionContainer>
[[maybe_unused]] void SegmentTree<T, BinaryFunctionContainer>::update(size_t pos, T val) {
    recursiveUpdate(0, 0, (1 << (depth - 1)) - 1, pos, val);
} // OK

class max{
public:

    long long operator() (long long a, long long b) {
        if (a > b) {
            return a;
        } else {
            return b;
        }
    };

    static long long neutral () {
        return -10000000;
    }

};

class min{
public:

    long long operator() (long long a, long long b) {
        if (a > b) {
            return b;
        } else {
            return a;
        }
    };

    static long long neutral () {
        return 10000000;
    }

};

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t queriesAmount;
    std::cin >> queriesAmount;
    long long a;
    long long b;

    std::vector<long long> base (100100);

    for (long long i = 1; i < 100100; ++i) {
        base[i] = ((i * i) % 12345) + ((i * i * i) % 23456);
    }

    SegmentTree<long long, min> minTree(base);
    SegmentTree<long long, max> maxTree(base);

    for (size_t i = 0; i < queriesAmount; ++i) {
        std::cin >> a >> b;
        if (a > 0) {
            std::cout << maxTree.request(a + 1, b + 1) - minTree.request(a + 1, b + 1) << '\n';
        } else {
            a *= -1;
            maxTree.update( a + 1, b);
            minTree.update(a + 1, b);
        }
    }



}
