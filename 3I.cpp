/*У художника-авангардиста есть полоска разноцветного холста. За один раз он перекрашивает некоторый отрезок полоски в некоторый цвет. После каждого перекрашивания специально обученный фотограф делает снимок части получившегося творения для музея современного искусства. Для правильного экспонирования требуется знать яркость самого темного цвета на выбранном фотографом отрезке. Напишите программу для определения яркости самого темного цвета на отрезке.

Требуемая скорость определения яркости — O(logN)
. Цвет задается тремя числами R
, G
 и B
 (0≤R,G,B≤255
), его яркость =R+G+B
. Цвет (R1,G1,B1)
 темнее цвета (R2,G2,B2)
, если R1+G1+B1<R2+G2+B2
.

Входные данные
Первая строка содержит число N
 —- длина отрезка (координаты [0...N−1]
, причём N≤30000
). Затем следует N
 строк по 3
 числа —- цвета отрезка. Следующая строка содержит число K
 —- количество перекрашиваний и фотографирований. Затем задано K
 строк, описывающих перекрашивание и фотографирование. В каждой такой строке 7
 натуральных чисел: C
, D
, R
, G
, B
, E
, F
, где [C,D]
 —- координаты перекрашиваемого отрезка, (R,G,B)
 —- цвет покраски, [E,F]
 —- фотографируемый отрезок.

Выходные данные
Требуется вывести K
 целых чисел. Каждое число —- яркость самого темного цвета на отрезке [E,F]
 после соответствующего окрашивания.*/

#include <iostream>
#include <vector>
#include <algorithm>

class SegmentTree {

private:

    std::vector<std::pair<int, int>> data;
    const int neutral = INT32_MAX;

public:

    explicit SegmentTree(int size);

    void build(const int base[], int left, int right, int index);

    void updateDownwards(int index);

    void setOnSegment(int index, int coveringLeft, int coveringRight, int left, int right, int val);

    int request(int index, int coveringLeft, int coveringRight, int left, int right);

};

SegmentTree::SegmentTree(int size) {

    data.reserve(4 * size);

}

void SegmentTree::build(const int *base, int left, int right, int index) {

    if (left == right) {

        data[index] = {base[left], -1};
        return;

    }

    int mid = (left + right) >> 1;

    build(base, left, mid, index * 2);
    build(base, mid + 1, right, 2 * index + 1);

    data[index] = std::min(data[2 * index], data[2 * index + 1]);

}

void SegmentTree::updateDownwards(int index) {

    if (data[index].second != -1) {

        int val = data[index].second;

        data[2 * index].first = val;
        data[2 * index + 1].first = val;
        data[2 * index].second = val;
        data[2 * index + 1].second = val;

        data[index].second = -1;

    }

}

void SegmentTree::setOnSegment(int index, int coveringLeft, int coveringRight, int left, int right, int val) {

    if (coveringLeft == left && coveringRight == right) {
        data[index].second = val;
        data[index].first = val;
        return;
    }

    updateDownwards(index);
    int mid = (coveringLeft + coveringRight) >> 1;

    if (left <= mid) {
        setOnSegment(2 * index, coveringLeft, mid, left, std::min(right, mid), val);
    }

    if (right > mid) {
        setOnSegment(2 * index + 1, mid + 1, coveringRight, std::max(mid + 1, left), right, val);
    }

    data[index].first = std::min(data[2 * index].first, data[2 * index + 1].first);

}

int SegmentTree::request(int index, int coveringLeft, int coveringRight, int left, int right) {

    if (left > right) {
        return (neutral);
    }

    if (left == coveringLeft && right == coveringRight) {
        return data[index].first;
    }

    updateDownwards(index);
    int mid = (coveringLeft + coveringRight) >> 1;

    return std::min(
            request(2 * index, coveringLeft, mid, left, std::min(right, mid)),
            request(2 * index + 1, mid + 1, coveringRight, std::max(left, mid + 1), right)
    );
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int segmentLength, Queries;
    int *segment;

    std::cin >> segmentLength;
    segment = new int[segmentLength];

    int redValue, greenValue, blueValue;

    for (int i = 0; i < segmentLength; ++i) {

        std::cin >> redValue >> greenValue >> blueValue;

        segment[i] = redValue + greenValue + blueValue;

    }

    SegmentTree tree(segmentLength);
    tree.build(segment, 0, segmentLength - 1, 1);

    std::cin >> Queries;

    int leftPaint, rightPaint, leftPhoto, rightPhoto;

    for (int i = 0; i < Queries; ++i) {

        std::cin >> leftPaint >> rightPaint >> redValue >> greenValue >> blueValue >> leftPhoto >> rightPhoto;

        tree.setOnSegment(1, 0, segmentLength - 1, leftPaint, rightPaint, redValue + greenValue + blueValue);

        std::cout << tree.request(1, 0, segmentLength - 1, leftPhoto, rightPhoto) << ' ';

    }

    std::cout << '\n';

    delete [] segment;
}
