/*Вася написал на длинной полоске бумаги большое число
 * и решил похвастаться своему старшему брату Пете этим достижением.
 * Но только он вышел из комнаты, чтобы позвать брата, как его сестра
 * Катя вбежала в комнату и разрезала полоску бумаги на несколько частей.
 * В результате на каждой части оказалось одна или несколько идущих подряд цифр.

Теперь Вася не может вспомнить, какое именно число он написал.
 Только помнит, что оно было очень большое. Чтобы утешить младшего брата,
 Петя решил выяснить, какое максимальное число могло быть написано на полоске бумаги перед разрезанием.
 Помогите ему!

Входные данные
Входной файл содержит одну или более строк,
 каждая из которых содержит последовательность цифр.
 Количество строк во входном файле не превышает 100,
 каждая строка содержит от 1 до 100 цифр.
 Гарантируется, что хотя бы в одной строке первая цифра отлична от нуля.

Выходные данные
Выведите в выходной файл одну строку — максимальное число,
 которое могло быть написано на полоске перед разрезанием.*/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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

class CompareCutParts {
public:
    bool operator() (std::string* obj1, std::string* obj2) {
        return ((*obj1 + *obj2) > (*obj2 + *obj1));
    }
};

int main() {

    std::vector<std::string> parts;
    std::ifstream fileInput;
    std::ofstream fileOutput;
    std::string str;
    fileInput.open("number.in");

    while (!fileInput.eof()) {
        fileInput >> str;
        parts.push_back(str);
    }

    parts.pop_back(); // for CF only, because of duplication bug

    fileInput.close();

    mergeSort<std::string, CompareCutParts>(&parts[0], parts.size());

    fileOutput.open("number.out");

    for (auto & part : parts) {
        fileOutput << part;
    }

    fileOutput.close();

}
