/*Реализуйте свой стек. Решения, использующие std::stack, получат 1 балл. Решения, хранящие стек в массиве, получат 1.5 балла. Решения, использующие указатели, получат 2 балла.

Гарантируется, что количество элементов в стеке ни в какой момент времени не превышает 10000.

Обработайте следующие запросы:

push n: добавить число n в конец стека и вывести «ok»;
pop: удалить из стека последний элемент и вывести его значение, либо вывести «error», если стек был пуст;
back: сообщить значение последнего элемента стека, либо вывести «error», если стек пуст;
size: вывести количество элементов в стеке;
clear: опустошить стек и вывести «ok»;
exit: вывести «bye» и завершить работу.
Входные данные
В каждой строке входных данных задана одна операция над стеком в формате, описанном выше.

Выходные данные
В ответ на каждую операцию выведите соответствующее сообщение.*/

#include <iostream>
#include <string>
#include <map>

// element of stack - node

struct node {
    int value;
    node* previous;
};

// stack - the class

class stack {
private:

    node* tail;

public:

    int size;

    void push(int value) {
        node* additionalNode = new node();
        additionalNode->value = value;
        additionalNode->previous = tail;
        tail = additionalNode;
        size++;
    }

    void pop(){
        if (size > 0) {
            node* previousNode = tail->previous;
            delete tail;
            tail = previousNode;
            size--;
        }
    }

    int top() {
        return tail->value;
    }

    [[nodiscard]] bool empty() const {
        return (size == 0);
    }

    void clear() {
        while (size > 0) {
            pop();
        }
    }

    stack() {
        size = 0;
        tail = nullptr;
    }

    ~stack() {
        clear();
    }

};

// map for switch statement in executor

int getCommandMap(const std::string& input) {
    static std::map<std::string, int> commandMap {
            {"exit",0},
            {"pop",1},
            {"push",2},
            {"back",3},
            {"size",4},
            {"clear",5},
    };
    return commandMap[input];
}

// executor executes the command according to the rules

void executor(const std::string& input, stack* theStack, bool* endProcess) {
    int newValue = 0;
    switch (getCommandMap(input))
    {
        case 0: //the exit case

            *endProcess = true;
            std::cout << "bye" << std::endl;
            break;

        case 1: // the pop case

            if (theStack->empty()) {
                std::cout << "error" << std::endl;
            } else {
                std::cout << theStack->top() << std::endl;
                theStack->pop();
            }
            break;

        case 2: // the push case

            std::cin >> newValue;
            theStack->push(newValue);
            std::cout << "ok" << std::endl;
            break;

        case 3: // the back case

            if (theStack->empty()) {
                std::cout << "error" << std::endl;
            } else {
                std::cout << theStack->top() << std::endl;
            }
            break;

        case 4: // the size case

            std::cout << theStack->size << std::endl;
            break;

        case 5: // the clear case

            theStack->clear();
            std::cout << "ok" << std::endl;
            break;

        default:

            break;

    }
}

// main body

int main() {

    bool endProcess = false;
    stack theStack;
    std::string input;


    while (!endProcess) {

        std::cin >> input;

        executor(input, &theStack, &endProcess);

    }

    return 0;
}
