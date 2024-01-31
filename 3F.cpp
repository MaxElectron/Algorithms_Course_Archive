/*В этой задаче используйте дерево Фенвика.
Вася любит наблюдать за звездами. Но следить за всем небом сразу ему тяжело. Поэтому он
наблюдает только за частью пространства, ограниченной кубом размером n×n×n. Этот куб поделен
на маленькие кубики размером 1 × 1 × 1. Во время его наблюдений могут происходить следующие
события:
1. В каком-то кубике появляются или исчезают несколько звезд.
2. К нему может заглянуть его друг Петя и поинтересоваться, сколько видно звезд в части пространства, состоящей из нескольких кубиков.
Формат входных данных
Первая строка входного файла содержит натуральное число 1 6 n 6 128. Координаты кубиков
— целые числа от 0 до n − 1. Далее следуют записи о происходивших событиях по одной в строке.
В начале строки записано число m. Если m равно:
1, то за ним следуют 4 числа — x, y, z (0 6 x, y, z < N) и k (−20000 6 k 6 20000) — координаты
кубика и величина, на которую в нем изменилось количество видимых звезд;
2, то за ним следуют 6 чисел — x1, y1, z1, x2, y2, z2 (0 6 x1 6 x2 < N, 0 6 y1 6 y2 < N,
0 6 z1 6 z2 < N), которые означают, что Петя попросил подсчитать количество звезд в
кубиках (x, y, z) из области: x1 6 x 6 x2, y1 6 y 6 y2, z1 6 z 6 z2;
3, то это означает, что Васе надоело наблюдать за звездами и отвечать на вопросы Пети. Эта
запись встречается во входном файле только один раз и будет последней записью.
Количество записей во входном файле не больше 100 002.
Формат выходных данных
Для каждого Петиного вопроса выведите на отдельной строке одно число — искомое количество
звезд.*/

#include <iostream>
#include <vector>

template <typename T, class Arithmetic>
class [[maybe_unused]] Fenwick {
private:

    std::vector<T> data;
    long long edgeLength;
    Arithmetic foo;

public:

    [[maybe_unused]] explicit Fenwick(std::vector<T> base, long long baseEdgeLength);

    [[maybe_unused]] void change(long long indexX, long long indexY, long long indexZ, T value);

    [[maybe_unused]] T sum(long long indexX, long long indexY, long long indexZ);

    [[maybe_unused]] T sum(long long indexX1, long long indexY1, long long indexZ1, 
                           long long indexX2, long long indexY2, long long indexZ2);

};

template<typename T, class Arithmetic>
[[maybe_unused]] Fenwick<T, Arithmetic>::Fenwick(std::vector<T> base, long long baseEdgeLength) {
    edgeLength = baseEdgeLength;
    data = std::vector<T> (base.size(), foo.neutral());
    for (long long i = 0; i < edgeLength; ++i) {
        for (long long j = 0; j < edgeLength; ++j) {
            for (long long k = 0; k < edgeLength; ++k) {
                change(i, j, k, base[i + (j * edgeLength) + (k * edgeLength * edgeLength)]);
            }
        }
    }
} // OK

template<typename T, class Arithmetic>
void Fenwick<T, Arithmetic>::change(long long int indexX, long long int indexY, long long int indexZ, T value) {
    for (long long i = indexX; i < edgeLength; i = (i | (i + 1))) {
        for (long long j = indexY; j < edgeLength; j = (j | (j + 1))) {
            for (long long k = indexZ; k < edgeLength; k = (k | (k + 1))) {
                data[i + (j * edgeLength) + (k * edgeLength * edgeLength)] += value;
            }
        }
    }
} // OK

template<typename T, class Arithmetic>
[[maybe_unused]] T Fenwick<T, Arithmetic>::sum(long long indexX, long long indexY, long long indexZ) {
    if (0 > indexX) {
        return foo.neutral();
    }
    if (0 > indexY) {
        return foo.neutral();
    }
    if (0 > indexZ) {
        return foo.neutral();
    }
    T ans = foo.neutral();
    for (long long i = indexX; i >= 0; i = (i & (i + 1)) - 1) {
        for (long long j = indexY; j >= 0; j = (j & (j + 1)) - 1) {
            for (long long k = indexZ; k >= 0; k = (k & (k + 1)) - 1) {
                ans += data[i + (j * edgeLength) + (k * edgeLength * edgeLength)];
            }
        }
    }
    return ans;
} // OK

template<typename T, class Arithmetic>
[[maybe_unused]] T Fenwick<T, Arithmetic>::sum(long long indexX1, long long indexY1, long long indexZ1,
                                               long long indexX2, long long indexY2, long long indexZ2) {
    if (indexX1 > indexX2) {
        return foo.neutral();
    }
    if (indexY1 > indexY2) {
        return foo.neutral();
    }
    if (indexZ1 > indexZ2) {
        return foo.neutral();
    }
    return foo(foo(foo(sum(indexX2, indexY2, indexZ2),
                       sum(indexX2, indexY1 - 1, indexZ1 - 1)),
                   foo(sum(indexX1 - 1, indexY2, indexZ1 - 1),
                       sum(indexX1 - 1, indexY1 - 1, indexZ2))),
               foo.negative(foo(foo(sum(indexX1 - 1, indexY2, indexZ2),
                                    sum(indexX2, indexY1 - 1, indexZ2)),
                                foo(sum(indexX2, indexY2, indexZ1 - 1),
                                    sum(indexX1 - 1, indexY1 - 1, indexZ1 - 1)))));
} // OK

template <typename T>
class Digits {
public:
    T operator() (T a, T b) {
        return a + b;
    }

    T neutral () {
        return 0;
    }

    T negative (T a) {
        return -a;
    }
};

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long edgeLength;
    std::cin >> edgeLength;
    std::vector<long long> base (edgeLength * edgeLength * edgeLength, 0);

    Fenwick<long long, Digits<long long>> stars(base, edgeLength);
    bool flag = false;
    int query;
    long long x1, y1, z1, x2, y2, z2, val;
    while (!flag) {
        std::cin >> query;
        switch (query) {
            case 1:
                std::cin >> x1 >> y1 >> z1 >> val;
                stars.change(x1, y1, z1, val);
                break;
            case 2:
                std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
                std::cout << stars.sum(x1, y1, z1,
                                       x2, y2, z2) << '\n';
                break;
            default:
                flag = true;
                break;
        }
    }

}
