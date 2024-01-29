/*Даны n нестрого возрастающих массивов Ai и m нестрого убывающих массивов Bj.
Все массивы имеют одну и ту же длину l.
Далее даны q запросов вида (i,j), ответ на запрос
– такое k, что max(Aik,Bjk) минимален.
Если таких k несколько, можно вернуть любое.

Входные данные
На первой строке числа n,m,l (1≤n,m≤900;1≤l≤3000).
Следующие n строк содержат описания массивов Ai.
Каждый массив описывается перечислением l элементов.
Элементы массива – целые числа от 0 до 105−1.
Далее число m и описание массивов Bj в таком же формате.
Массивы и элементы внутри массива нумеруются с 1.
На следюущей строке число запросов q (1≤q≤n⋅m).
Следующие q строк содержат пары чисел i,j (1≤i≤n, 1≤j≤m).

Выходные данные
Выведите q чисел от 1 до l – ответы на запросы.*/

#include <iostream>
#include <vector>

int findTheOptimalIndex(const int* increasingArrayPointer, const int* decreasingArrayPointer, const int* sizeOfArray) {
    if (*(increasingArrayPointer + *sizeOfArray  - 1) <= *(decreasingArrayPointer + *sizeOfArray  - 1)) {
        return (*sizeOfArray  - 1);
    }
    if (*(increasingArrayPointer) >= *(decreasingArrayPointer)) {
        return 0;
    }
    int runningBottom = 0;
    int runningTop = *sizeOfArray;
    int median = runningTop;
    while (runningBottom < runningTop) {
        if (runningTop - 1 == median) {
            break;
        }
        median = (runningTop + runningBottom) / 2;
        if (*(increasingArrayPointer + median) >= *(decreasingArrayPointer + median)) {
            runningTop = median;
        } else {
            runningBottom = median;
        }
    }
    if (runningTop == 0) {
        return 0;
    }
    if (*(increasingArrayPointer + runningTop) > *(decreasingArrayPointer + runningTop - 1)) {
        return runningTop - 1;
    } else {
        return runningTop;
    }
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int incrementArrays = 0;
    int decrementArrays = 0;
    int sizeOfArray = 0;

    std::cin >> incrementArrays;
    std::cin >> decrementArrays;
    std::cin >> sizeOfArray;

    int totalArrays = decrementArrays + incrementArrays;
    std::vector<int> arrays(totalArrays * sizeOfArray);
    std::vector<int> answers(incrementArrays * decrementArrays, -1);

    for(int i = 0; i < totalArrays; ++i) {
        for (int j = 0; j < sizeOfArray; ++j) {
            std::cin >> arrays[i * sizeOfArray + j];
        }
    }

    int queriesAmount = 0;
    int incrementIndex = 0;
    int decrementIndex = 0;
    std::cin >> queriesAmount;

    for (int i = 0; i < queriesAmount; ++i) {
        std::cin >> incrementIndex;
        std::cin >> decrementIndex;
        --incrementIndex;
        --decrementIndex;
        if (answers[incrementIndex * decrementArrays + decrementIndex] == -1) {
            answers[incrementIndex * decrementArrays + decrementIndex] = findTheOptimalIndex(
                    &(arrays[incrementIndex * sizeOfArray]),
                    &(arrays[(decrementIndex + incrementArrays) * sizeOfArray]),
                    &sizeOfArray
                    ) + 1;
        }
        std::cout << answers[incrementIndex * decrementArrays + decrementIndex] << '\n';
    }

    return 0;
}
