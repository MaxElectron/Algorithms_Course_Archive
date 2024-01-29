/*Напишите программу, которая для заданного массива A=⟨a1,a2,…,an⟩ находит количество пар (i,j) таких,
 что i<j и ai>aj. Обратите внимание на то, что ответ может не влезать в int.

Входные данные
Первая строка входного файла содержит натуральное число n (1⩽n⩽100000) — количество элементов массива.
Вторая строка содержит n попарно различных элементов массива A — целых неотрицательных чисел,
не превосходящих 109.

Выходные данные
В выходной файл выведите одно число — ответ на задачу.*/

#include <iostream>
#include <vector>
#include <fstream>

int mergeSortAndInverseCount(int* Array, int sizeOfArray) {
    
    if (sizeOfArray <= 1) {
        return 0;
    }
    int inversionsInLeftPart;
    int inversionsInRightPart;
    int newInversions = 0;
    
    //split
    inversionsInLeftPart = mergeSortAndInverseCount(Array, sizeOfArray/2);
    inversionsInRightPart = mergeSortAndInverseCount(Array + sizeOfArray/2,(sizeOfArray + 1) / 2);
    
    //merge
    int leftInLeft = sizeOfArray/2;
    int* leftPointer = Array;
    int* rightPointer = Array + sizeOfArray/2;
    std::vector<int> sortedArray;
    for(int i = 0; i < sizeOfArray; ++i) {

        if(*leftPointer <= *rightPointer) {
            sortedArray.push_back(*leftPointer);
            ++leftPointer;
            --leftInLeft;
        } else {
            sortedArray.push_back(*rightPointer);
            ++rightPointer;
            newInversions += leftInLeft;
        }

        if(leftPointer == Array + sizeOfArray / 2) {
            while (i < sizeOfArray) {
                sortedArray.push_back(*rightPointer);
                ++rightPointer;
                ++i;
            }
        }

        if(rightPointer == Array + sizeOfArray) {
            while (i < sizeOfArray) {
                sortedArray.push_back(*leftPointer);
                ++leftPointer;
                ++i;
            }
        }
    }

    //transfer
    for(int i = 0; i < sizeOfArray; ++i) {
        *Array = sortedArray[i];
        ++Array;
    }
    return newInversions + inversionsInRightPart + inversionsInLeftPart;

}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::ifstream inverseFileInput;
    inverseFileInput.open("inverse.in");

    int sizeOfArray = 0;
    inverseFileInput >> sizeOfArray;
    int input = 0;
    std::vector<int> Array;

    for (int i = 0; i < sizeOfArray; ++i) {
        inverseFileInput >> input;
        Array.push_back(input);
    }


    std::ofstream inverseFileOutput;
    inverseFileOutput.open("inverse.out");
    inverseFileOutput << mergeSortAndInverseCount(&Array[0], sizeOfArray);

    return 0;
}
