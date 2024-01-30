/*Пусть есть мультимножество целых чисел (множество с возможными повторениями).
 * Необходимо реализовать структуру данных для их хранения, поддерживающую следующие операции:

GetMin — извлечение минимума;
GetMax — извлечение максимума;
Insert(A) — добавление числа A в множество.
Обратите внимание: название операций отличается от классического.

Входные данные
В первой строке входного файла записано одно целое число N (1≤N≤105) — число запросов к структуре.
 Затем в N строках следуют запросы по одному в строке: GetMin, GetMax, Insert(A) —
 извлечение минимума, максимума и добавление числа A (1≤A≤231−1).
 Запросы корректны, то есть нет операций извлечения для пустого множества.

Выходные данные
Для каждого запроса GetMin или GetMax выведите то число, которое было извлечено.*/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <sstream>

template<class T, class Comparator>
class Heap{
private:

    std::vector<unsigned long long> keys;
    std::vector<T> containedObjects;
    std::vector<unsigned long long> containedKeys;
    unsigned long long queries = 0;
    Comparator comparator;

    T* getFirst() {
        if (size() == 0) {
            return nullptr;
        } else {
            return &containedObjects[0];
        }
    }

    T* getLast() {
        if (size() == 0) {
            return nullptr;
        } else {
            return &containedObjects[size() - 1];
        }
    }

    void swap(T* obj1, T* obj2) {

        //swap key values
        unsigned long long tmpVal = containedKeys[obj1 - getFirst()];
        containedKeys[obj1 - getFirst()] = containedKeys[obj2 - getFirst()];
        containedKeys[obj2 - getFirst()] = tmpVal;

        //swap values
        T tmpObj = *obj1;
        *obj1 = *obj2;
        *obj2 = tmpObj;

        //swap key pointers
        unsigned long long tmpPtr = keys[containedKeys[obj1 - getFirst()]];
        keys[containedKeys[obj1 - getFirst()]] = keys[containedKeys[obj2 - getFirst()]];
        keys[containedKeys[obj2 - getFirst()]] = tmpPtr;
    }

    bool isRoot(T* obj) {
        if (obj - getFirst() == 0) {
            return true;
        } else {
            return false;
        }
    }

    int downwardsDegree(T* obj) {
        if (size() > ((obj - getFirst()) * 2) + 2) {
            return 2;
        }
        if (size() == ((obj - getFirst()) * 2) + 2) {
            return 1;
        }
        return 0;
    }

    T* firstChildOf(T* obj) {
        if (downwardsDegree(obj) >= 1) {
            return getFirst() + ((obj - getFirst()) * 2) + 1;
        } else {
            return nullptr;
        }
    }

    T* secondChildOf(T* obj) {
        if (downwardsDegree(obj) >= 2) {
            return getFirst() + ((obj - getFirst()) * 2) + 2;
        } else {
            return nullptr;
        }
    }

    T* parentOf(T* obj) {
        if (isRoot(obj)) {
            return nullptr;
        } else {
            return getFirst() + (((obj - getFirst()) - ((obj - getFirst() + 1) % 2)) / 2);
        }
    }

    void siftDown(T* obj) {
        switch (downwardsDegree(obj)) {
            case 0:
                break;

            case 1:
                if (!comparator(obj, firstChildOf(obj))) {
                    assert(comparator(firstChildOf(obj), obj));
                    swap(obj, firstChildOf(obj));
                }
                break;

            case 2:
                if (comparator(firstChildOf(obj), secondChildOf(obj))) {
                    if (!comparator(obj, firstChildOf(obj))) {
                        assert(comparator(firstChildOf(obj), obj));
                        swap(obj, firstChildOf(obj));
                        siftDown(firstChildOf(obj));
                    }
                } else {
                    assert(comparator(secondChildOf(obj), firstChildOf(obj)));
                    if (!comparator(obj, secondChildOf(obj))) {
                        assert(comparator(secondChildOf(obj), obj));
                        swap(obj, secondChildOf(obj));
                        siftDown(secondChildOf(obj));
                    }
                }
                break;
        }
    }

    void siftUp(T* obj) {
        if (!isRoot(obj)) {
            if (!comparator(parentOf(obj), obj)) {
                assert(comparator(obj, parentOf(obj)));
                swap(obj, parentOf(obj));
                siftUp(parentOf(obj));
            }
        }
    }

public:
    void insert(T obj) {
        containedObjects.push_back(obj);
        containedKeys.push_back(queries);
        keys.push_back(size() - 1);
        siftUp(getLast());
        ++queries;
    }; //used only from outside

    T getRoot() {
        assert(!containedObjects.empty());
        return containedObjects[0];
    }

    void deleteKey(unsigned long long key) {
        unsigned long long keyPreservation = keys[key];
        keys[key] = 42;

        if (keyPreservation == size() - 1) {
            containedObjects.pop_back(); //remove last element
            containedKeys.pop_back();
            keys.push_back(42);
            ++queries;
            return;
        }

        containedObjects[keyPreservation] = containedObjects[size() - 1];
        containedKeys[keyPreservation] = containedKeys[size() - 1];
        keys[containedKeys[size() - 1]] = keyPreservation;

        containedObjects.pop_back(); //remove getLast() element
        containedKeys.pop_back();

        siftDown(&containedObjects[keyPreservation]);
        siftUp(&containedObjects[keyPreservation]);

        keys.push_back(42);
        ++queries;
    }

    unsigned long long getRootKey() {
        assert(!containedObjects.empty());
        return containedKeys[0];
    }

    unsigned long long size() {
        return containedObjects.size();
    }

};

class isLess {
public:
    bool operator() (const long long* obj1, const long long* obj2) {
        return *obj1 <= *obj2;
    }
};

class isGreater {
public:
    bool operator() (const long long* obj1, const long long* obj2) {
        return *obj1 >= *obj2;
    }
};

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    unsigned long long queriesAmount;
    long long newValue;
    unsigned long long key;
    std::cin >> queriesAmount;

    Heap<long long, isLess> minHeap;
    Heap<long long, isGreater> maxHeap;
    std::string command;
    std::stringstream ss;

    for (unsigned long long i = 0; i < queriesAmount; ++i) {
        std::cin >> command;
        if ((command >= "Insert(")) {
            ss.str("");
            ss << (command.substr(command.find('(') + 1, (command.find(')') - command.find('('))));
            ss >> newValue;
            minHeap.insert(newValue);
            maxHeap.insert(newValue);
            continue;
        }
        if ((command == "GetMin") || (command == "min")) {
            key = minHeap.getRootKey();
            std::cout << minHeap.getRoot() << '\n';
            maxHeap.deleteKey(key);
            minHeap.deleteKey(key);
            continue;
        }
        if ((command == "GetMax") || (command == "max")) {
            key = maxHeap.getRootKey();
            std::cout << maxHeap.getRoot() << '\n';
            minHeap.deleteKey(key);
            maxHeap.deleteKey(key);
            continue;
        }
        --i;
    }
}
