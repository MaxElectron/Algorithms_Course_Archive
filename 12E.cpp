/*Дан n
-угольник и m
 точек. Для каждой из точек определите, лежит ли она внутри, вне или на границе многоугольника.

Входные данные
В первой строке даны два целых числа, n
 и m
 (3≤n≤105
, 1≤m≤104
, n⋅m≤108
).

В следующих n
 строках задаются координаты вершин многоугольника в порядке обхода.

В следующих m
 строках задаются координаты точек, которые нужно проверить на принадлежность многоугольнику.

Все координаты — целые числа, по абсолютной величине не превосходящие 109
.

Выходные данные
Для каждой точки выведите ответ на отдельной строке: «INSIDE», если точка лежит строго внутри многоугольника, «BOUNDARY», если она лежит на его границе, и «OUTSIDE» иначе.*/

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
    int relative_pos(point<T> origin, std::vector<point<T>> &polygon)
    {
        int winding_number = 0; // it is actually roughly doubled for execution purposes, sorry for that
        vector<T> reference_vector (origin, polygon[0]); // defines neutral direction

        for (size_t i = 1; i <= polygon.size(); i++)
        {
            vector<T> first (origin, polygon[i - 1]);
            vector<T> second (origin, polygon[i % polygon.size()]);
            bool first_neutral = !(first & reference_vector) && (sign_of(first * reference_vector) > 0);
            bool second_neutral = !(second & reference_vector) && (sign_of(second * reference_vector) > 0);

            if ((origin.x == polygon[i % polygon.size()].x) && (origin.y == polygon[i % polygon.size()].y))
            // check if i-th vertex matches origin
            {
                return 0; // boundary case
            }
            
            // check if i - (i+1) segment goes...
            if (!(first & second) && (sign_of(first * second) < 0))
            // through origin
            {
                return 0; // boundary case
            }
            if (first_neutral && second_neutral)
            // remains neutral
            {
                continue;
            }
            if (first_neutral)
            // from neutral into any direction
            {
                winding_number += sign_of(reference_vector & second);
            }
            if (second_neutral)
            // into neutral from any direction
            {
                winding_number -= sign_of(reference_vector & first);
            }
            if (!(sign_of(reference_vector & second) + sign_of(reference_vector & first)))
            // changes direction ...
            {
                if ((sign_of(reference_vector & second) == sign_of(first & second)))
                // through neutral
                {
                    winding_number += 2 * sign_of(reference_vector & second);
                }
            }
        }

        if (winding_number)
        {
            return 1; // inside case
        }

        return -1; // outside case
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
    int n, m;

    std::cin >> n >> m;

    std::vector<geometry::point<long long>> polygon(n);

    for (geometry::point<long long> &vertex : polygon)
    {
        std::cin >> vertex.x >> vertex.y;
    }

    geometry::point<long long> origin;
    for (size_t i = 0; i < m; i++)
    {
        std::cin >> origin.x >> origin.y;

        switch (geometry::relative_pos(origin, polygon))
        {
        case 1:
            std::cout << "INSIDE\n";
            break;
        case -1:
            std::cout << "OUTSIDE\n";
            break;
        default:
            std::cout << "BOUNDARY\n";
        }
    }
    
}
