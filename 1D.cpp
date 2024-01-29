/*блины Мглистых гор очень любях ходить к своим шаманам. Так как гоблинов много, к шаманам часто образуются очень длинные очереди. А поскольку много гоблинов в одном месте быстро образуют шумную толку, которая мешает шаманам проводить сложные медицинские манипуляции, последние решили установить некоторые правила касательно порядка в очереди.

Обычные гоблины при посещении шаманов должны вставать в конец очереди. Привилегированные же гоблины, знающие особый пароль, встают ровно в ее середину, причем при нечетной длине очереди они встают сразу за центром.

Так как гоблины также широко известны своим непочтительным отношением ко всяческим правилам и законам, шаманы попросили вас написать программу, которая бы отслеживала порядок гоблинов в очереди.

Входные данные
В первой строке входных данный записано число N
 (1≤N≤105)
  −
 количество запросов. Следующие N
 строк содержат описание запросов в формате:

+ i
  −
 гоблин с номером i
 (1≤i≤N)
 встаёт в конец очереди.
* i
  −
 привилегированный гоблин с номером i встает в середину очереди.
-  −
 первый гоблин из очереди уходит к шаманам. Гарантируется, что на момент такого запроса очередь не пуста.
Выходные данные
Для каждого запроса типа - программа должна вывести номер гоблина, который должен зайти к шаманам.*/

#include <iostream>
#include <deque>

namespace goblins {

    std::deque<int> firstHalf;
    std::deque<int> secondHalf;
    bool even = true;

}

void callGoblin() {
    goblins::even = !goblins::even;
    std::cout << goblins::firstHalf.front() << std::endl;
    goblins::firstHalf.pop_front();
    if(!goblins::even) {
        goblins::firstHalf.push_back(goblins::secondHalf.front());
        goblins::secondHalf.pop_front();
    }
}

void endPush() {
    goblins::even = !goblins::even;
    int goblin;
    std::cin >> goblin;
    goblins::secondHalf.push_back(goblin);
    if(!goblins::even) {
        goblins::firstHalf.push_back(goblins::secondHalf.front());
        goblins::secondHalf.pop_front();
    }

}

void middlePush() {
    goblins::even = !goblins::even;
    int goblin;
    std::cin >> goblin;
    if (!goblins::even) {
        goblins::firstHalf.push_back(goblin);
    } else {
        goblins::secondHalf.push_front(goblin);
    }

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int goblinsAmount;
    char command;
    std::cin >> goblinsAmount;
    for (int i = 0; i < goblinsAmount; i++) {
        std::cin >> command;
        if ( command == '-') callGoblin();
        if ( command == '+') endPush();
        if ( command == '*') middlePush();
    }

    return 0;
}
