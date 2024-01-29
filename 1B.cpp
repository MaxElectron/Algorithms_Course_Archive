/*По заданной строке из круглых/квадратных/фигурных открывающих и закрывающих скобок определить, является ли она правильной скобочной последовательностью.

Множество правильных скобочных последовательностей (ПСП) определяется как наименьшее множество с условиями:

пустая строка является ПСП;
если S — ПСП, то (S), [S], {S} — тоже ПСП;
если S1 и S2 — ПСП, то S1S2 — тоже ПСП.
Входные данные
В единственной строке содержится последовательность из круглых/квадратных/фигурных открывающих и закрывающих скобок.

Выходные данные
Выведите «yes», если введённая строка является правильной скобочной последовательностью, и «no» иначе.*/

#include <iostream>
#include <stack>
#include <string>

bool checkNextBracket(char nextBracket, std::stack<char>* partitionedBracketSequence) {

    if ((nextBracket == ')') && ((partitionedBracketSequence->empty()) || (partitionedBracketSequence->top() != '('))) {
        return false;
    }
    if ((nextBracket == ']') && ((partitionedBracketSequence->empty()) || (partitionedBracketSequence->top() != '['))) {
        return false;
    }
    if ((nextBracket == '}') && ((partitionedBracketSequence->empty()) || (partitionedBracketSequence->top() != '{'))) {
        return false;
    }
    if ((nextBracket == '(') || (nextBracket == '[') || (nextBracket == '{')) {
        partitionedBracketSequence->push(nextBracket);
    } else {
        partitionedBracketSequence->pop();
    }
    return true;
}

int main() {

    std::string bracketSequence;
    std::cin >> bracketSequence;
    std::stack<char> partitionedBracketSequence;
    std::string answer = "yes";

    for (char i : bracketSequence) {
        if (!checkNextBracket(i, &partitionedBracketSequence)) {
            answer = "no";
            break;
        }
    }
    if (!partitionedBracketSequence.empty()) {
        answer = "no";
    }

    std::cout << answer;

    return 0;
}
