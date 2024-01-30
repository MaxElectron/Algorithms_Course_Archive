/*На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка [Li,Ri].
 * Найти сумму длин частей числовой прямой, окрашенных ровно в один слой. N≤10000.
 * Li,Ri — целые числа в диапазоне [0,109].

Входные данные
В первой строке записано количество отрезков. В каждой последующей строке через
 пробел записаны координаты левого и правого концов отрезка.

Выходные данные
Выведите целое число — длину окрашенной в один слой части.*/

#include <iostream>
#include <vector>

template<class T, class Compare>

void mergeSort(T* array, unsigned long sizeOfArray) {

    static Compare compare;

    if (sizeOfArray <= 1){
        return;
    }

    //split
    mergeSort<T , Compare>(array, sizeOfArray/2);
    mergeSort<T , Compare>(array + sizeOfArray/2,(sizeOfArray + 1) / 2);

    //merge
    unsigned long leftInLeft = sizeOfArray/2;
    T* leftPointer = array;
    T* rightPointer = array + sizeOfArray/2;
    std::vector<T> sortedArray;
    for(int i = 0; i < sizeOfArray; ++i) {

        if(compare(leftPointer, rightPointer)) {
            sortedArray.push_back(*leftPointer);
            ++leftPointer;
            --leftInLeft;
        } else {
            sortedArray.push_back(*rightPointer);
            ++rightPointer;
        }

        if(leftPointer == array + sizeOfArray / 2) {
            while (rightPointer < array + sizeOfArray) {
                sortedArray.push_back(*rightPointer);
                ++rightPointer;
                ++i;
            }
        }

        if(rightPointer == array + sizeOfArray) {
            while (leftPointer < array + sizeOfArray / 2) {
                sortedArray.push_back(*leftPointer);
                ++leftPointer;
                ++i;
            }
        }
    }

    //transfer
    for(int i = 0; i < sizeOfArray; ++i) {
        *array = sortedArray[i];
        ++array;
    }

    }

class isToTheLeft {
public:
    bool operator() (const long long* obj1, const long long* obj2) {
        return std::abs(*obj1) < std::abs(*obj2);
    }
};

int main() {

     long long n = 0;
    std::cin >> n;
    std::vector< long long> ends(2 * n);

    for ( long long i = 0; i < 2 * n; i += 2) {
        std::cin >> ends[i];
        ++ends[i];
        std::cin >> ends[i+1];
        ++ends[i + 1];
        ends[i+1] *= -1;
    }

    mergeSort< long long, isToTheLeft>(&ends[0], 2*n);

     long long current = 0;
     long long length = 0;

    for ( long long i = 0; i < 2 * n; ++i) {
        if ((current == 1) && (i > 0)) {
            length += std::abs(ends[i]) - std::abs(ends[i-1]);
        }
        if (ends[i] > 0) {
            ++current;
        } else {
            --current;
        }
    }

    std::cout << length;

}
