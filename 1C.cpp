/*Гистограмма является многоугольником, сформированным из последовательности прямоугольников, выровненных на общей базовой линии. Прямоугольники имеют равную ширину, но могут иметь различные высоты. Обычно гистограммы используются для представления дискретных распределений, например, частоты символов в текстах. Отметьте, что порядок прямоугольников очень важен. Вычислите область самого большого прямоугольника в гистограмме, который также находится на общей базовой линии.

Входные данные
В первой строке входного файла записано число N (0<N≤106)  − количество прямоугольников гистограммы. Затем следует N целых чисел h1…hn, где 0≤hi≤109. Эти числа обозначают высоты прямоугольников гистограммы слева направо. Ширина каждого прямоугольника равна 1.

Выходные данные
Выведите площадь самого большого прямоугольника в гистограмме. Помните, что этот прямоугольник должен быть на общей базовой линии.*/

#include <iostream>
#include <vector>
#include <stack>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int barGraphLength;
    std::cin >> barGraphLength;

    std::vector<long long> barGraph;
    std::vector<long long> leftEdges;
    std::vector<long long> rightEdges;
    std::stack<long long> edge;
    long long input;
    long long answer = 0;

    for(int i = 0; i < barGraphLength; i++) {
        std::cin >> input;
        barGraph.push_back(input);
    }

    for(int i = 0; i < barGraphLength; i++) {
        while(!edge.empty() && barGraph[edge.top()] >= barGraph[i]) {
            edge.pop();
        }
        if(edge.empty()) {
            leftEdges.push_back(-1);
        } else {
            leftEdges.push_back(edge.top());
        }
        edge.push(i);
    }

    while (!edge.empty()) {
        edge.pop();
    }

    for(int i = barGraphLength - 1; i >= 0; i--) {
        while(!edge.empty() && barGraph[edge.top()] >= barGraph[i]) {
            edge.pop();
        }
        if(edge.empty()) {
            rightEdges.push_back(barGraphLength);
        } else {
            rightEdges.push_back(edge.top());
        }
        edge.push(i);
    }

    for(int i = 0; i < barGraphLength; i++) {
        if ((rightEdges[barGraphLength - i - 1] - leftEdges[i] - 1) * (barGraph[i]) > answer) {
            answer = (rightEdges[barGraphLength - i - 1] - leftEdges[i] - 1) * (barGraph[i]);
        }
    }

    std::cout << answer;

    return 0;
}
