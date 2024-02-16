/*Даны коэффициенты A1
, B1
, C1
 уравнения первой прямой и коэффициенты A2
, B2
, C2
 уравнения второй прямой. Требуется:

Построить направляющие векторы для обеих прямых (вывести координаты) в формате (−B,A)
Найти точку пересечения двух прямых или вычислить расстояние между ними, если они параллельны
Входные данные
В первой строке входного файла находятся три числа — коэффициенты нормального уравнения для первой прямой. Во второй строке — коэффициенты для второй прямой.

Все числа во входном файле по модулю не превосходят 10000
.

Выходные данные
В каждой строке выходного файла выведите ответ на соответствующий пункт задачи с точностью до 10−6
.

*/

#include <cmath>
#include <iomanip>
#include <iostream>

namespace geometry
{

    template <typename T>
    struct point
    {
        T x, y;
        point(T x_value, T y_value) : x(x_value), y(y_value) {}

        bool operator==(point other)
        {
            return (x == other.x) && (y == other.y);
        };
    };

    template <typename T>
    struct line
    {
        T a, b, c;
        line(T a_value, T b_value, T c_value) : a(a_value), b(b_value), c(c_value){};

        [[nodiscard]] point<T> direction()
        {
            // returns
            if (a < b)
            {
                a *= -1;
                b *= -1;
                c *= -1;
            }

            return {(-b) / std::sqrt(a * a + b * b), (a) / std::sqrt(a * a + b * b)};
        }
    };

    template <typename T>
    point<T> intersect(line<T> l1, line<T> l2)
    {
        // accepts two non-parallel lines
        return {(l1.b * l2.c - l2.b * l1.c) / (l1.a * l2.b - l2.a * l1.b), (l1.c * l2.a - l2.c * l1.a) / (l1.a * l2.b - l2.a * l1.b)};
    };

    template <typename T>
    T dist(line<T> l1, line<T> l2)
    {
        // accepts two parallel lines
        return std::abs(l1.c / std::sqrt(l1.a * l1.a + l1.b * l1.b) - l2.c / std::sqrt(l2.a * l2.a + l2.b * l2.b));
    };
}

int main()
{

    long double a, b, c;

    std::cin >> a >> b >> c;
    geometry::line<long double> l1(a, b, c);

    std::cin >> a >> b >> c;
    geometry::line<long double> l2(a, b, c);

    std::cout << std::setprecision(10);

    // quick fix because test doesn't accept normalized direction vectors - don't output them, just give coefficients

    std::cout << -l1.b << ' ' << l1.a << '\n';

    std::cout << -l2.b << ' ' << l2.a << '\n';

    if (l1.direction() == l2.direction())
    {
        std::cout << geometry::dist(l1, l2);
    }
    else
    {
        geometry::point<long double> intersection = geometry::intersect(l1, l2);

        std::cout << intersection.x << ' ' << intersection.y;
    }
}
