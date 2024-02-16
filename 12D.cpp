/*Проверьте многоугольник на выпуклость. Точки могут лежать на сторонах многоугольника (в этом случае выпуклость не нарушается).

Входные данные
В первой строке одно число N
 (3≤N≤100000
). Далее в N
 строках по паре целых чисел — координаты очередной вершины простого многоугольника в порядке обхода по или против часовой стрелки.

Координаты всех точек целые, по модулю не превосходят 107
.

Выходные данные
Одна строка «YES», если приведённый многоугольник является выпуклым, и «NO» в противном случае.*/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <vector>

// from https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
template <typename T>
int sign_of(T val)
{
    return (T(0) < val) - (val < T(0));
}

// did full rework
// rewrote geometry for consiseness and whole-number operations presicion
// still not bothered with const tag though

namespace geometry
{

    template <typename T>
    struct point
    {
        T x, y;
        point() : x(0), y(0) {}
        point(T x_value, T y_value) : x(x_value), y(y_value) {}
    };

    template <typename T>
    struct vector
    {
        T x, y;
        // constructors
        vector() : x(0), y(0) {}
        vector(T x_value, T y_value) : x(x_value), y(y_value) {}
        vector(T x_start, T y_start, T x_end, T y_end) : x(x_end - x_start), y(y_end - y_start) {}
        vector(point<T> value) : x(value.x), y(value.y) {}
        vector(point<T> start, point<T> end) : x(end.x - start.x), y(end.y - start.y) {}

        // operations
        T lenght()
        {
            if (std::is_integral<T>::value)
            {
                return T(std::round(std::sqrt(double(x * x + y * y))));
            }
            return T(std::sqrt(x * x + y * y));
        }

        vector &operator-()
        {
            x *= -1;
            y *= -1;
            return *this;
        }

        vector &operator+=(vector rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        vector &operator-=(vector rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        friend vector operator+(vector lhs, vector &rhs)
        {
            lhs += rhs;
            return lhs;
        }

        friend vector operator-(vector lhs, vector &rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        // product value
        friend T operator*(vector &lhs, vector &rhs)
        {
            return lhs.x * rhs.x + lhs.y * rhs.y;
        }

        // vector product value
        friend T operator&(vector &lhs, vector &rhs)
        {
            return lhs.x * rhs.y - lhs.y * rhs.x;
        }
    };

    // polygon related magic:
    // so not to inherit from std::vector those functions accept vector of points as a polygon and perform different tricks

    template <typename T>
    bool is_convex(std::vector<point<T>> &polygon)
    {

        int sign = 0;

        for (size_t i = 1; i < polygon.size() + 1; i++)
        // avoid sides with negative indexes - don't forget to "% polygon.size()" everything out there))
        {

            vector<T> prev(polygon[i - 1], polygon[i % polygon.size()]);
            vector<T> next(polygon[i % polygon.size()], polygon[(i + 1) % polygon.size()]);

            if (!(prev & next))
            // check if i-th vertex is alligned
            {
                if (sign_of(prev * next) < 0)
                // check if turn-back
                {
                    return false;
                }
            }
            else
            {
                if (!sign)
                // update sign if found first oriented turn, which happened to be at i-th vertex
                {
                    sign = sign_of(prev & next);
                }
                if (sign * sign_of(prev & next) == -1)
                // check for orientation not matching the previous ones (if any)
                {
                    return false;
                }
            }
        }

        return true;
    }

    // ostream interactions from https://stackoverflow.com/questions/23063838/making-a-custom-class-ostream-outputable
    template <typename T>
    std::ostream &operator<<(std::ostream &os, const vector<T> &v)
    {
        os << v.x << ' ' << v.y;
        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const point<T> &v)
    {
        os << v.x << ' ' << v.y;
        return os;
    }

}

int main()
{
    int n;

    std::cin >> n;

    std::vector<geometry::point<long long>> polygon(n);

    for (geometry::point<long long> &vertex : polygon)
    {
        std::cin >> vertex.x >> vertex.y;
    }

    if (geometry::is_convex(polygon))
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
}
