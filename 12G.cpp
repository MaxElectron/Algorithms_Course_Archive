/*Дан простой многоугольник на n
 вершинах. Найдите число его триангуляций по модулю 109 + 7
. Каждая сторона каждого треугольника триангуляции должна содержать ровно две вершины многоугольника.

Входные данные
В первой строке записано целое число n
 (3≤n≤200)
 — количество вершин многоугольника. Затем следует n
 строк, каждая строка содержит два целых числа: i
-я строка содержит xi,yi
 (|xi|,|yi|≤107)
 — i
-ю вершину многоугольника в порядке обхода по или против часовой стрелки.

Гарантируется, что многоугольник простой.

Выходные данные
Выведите количество способов по модулю 109 + 7
.*/

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <vector>
 
const long long MOD = 1000000007;
 
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
    point<T> middle(point<T> a, point<T> b)
    {
        return {(a.x + b.x) / 2, (a.y + b.y) / 2};
    }
 
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
 
    template <typename T>
    bool is_intersecting(point<T> a, point<T> b, point<T> c, point<T> d)
    {
        vector<T> ab(a, b);
        vector<T> ac(a, c);
        vector<T> ad(a, d);
        vector<T> bd(b, d);
        vector<T> cd(c, d);
 
        if (!((ab & ac) || (ab & ad) || (ac & ad)))
        // check for the alligned case
        {
            if ((std::sqrt(ab.x * ab.x + ab.y * ab.y) + std::sqrt(cd.x * cd.x + cd.y * cd.y)) >= (std::sqrt(ac.x * ac.x + ac.y * ac.y) + std::sqrt(bd.x * bd.x + bd.y * bd.y)))
            // check for AB and CD being longer ~ intersecting
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if ((std::abs(ac & ad) <= std::abs((ac & ab) + (ab & ad))) && (0 <= sign_of(ac & ab) * sign_of(ab & ad)) && (0 <= sign_of(ac & ab) * sign_of(ac & ad)) && (0 <= sign_of(ab & ad) * sign_of(ac & ad)))
            // if ACBD area is greater than ACD area and from A the orientations of ABC, ABD and ACD are the same - the segments intersect
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
 
    // polygon related magic:
    // so not to inherit from std::vector those functions accept vector of points as a polygon and perform different tricks
 
    template <typename T>
    int relative_pos(point<T> origin, std::vector<point<T>> &polygon)
    {
        int winding_number = 0;                         // it is actually roughly doubled for execution purposes, sorry for that
        vector<T> reference_vector(origin, polygon[0]); // defines neutral direction
 
        for (size_t i = 1; i <= polygon.size(); i++)
        {
            vector<T> first(origin, polygon[i - 1]);
            vector<T> second(origin, polygon[i % polygon.size()]);
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
 
    template <typename T>
    size_t triangulation_count(std::vector<point<T>> &polygon)
    // reworked this segment because the others were already working fine
    {
        // to be able to take middle of any segment scale everything up by factor of 2
        for (point<T> &v : polygon)
        {
            v.x *= 2;
            v.y *= 2;
        }
 
        // dp[i][j] will be the number of triangulations of segment from vertex i to vertex j
        std::vector<std::vector<long long>> dp(polygon.size() - 1, std::vector<long long>(polygon.size(), 0));
 
        for (long long i = polygon.size() - 2; i > -1; i--)
        // move segment start from the polygon end to the polygon start
        {
 
            dp[i][i + 1] = 1; // there's one triangulation of a segment only
 
            for (size_t j = i + 2; j < polygon.size(); j++)
            // move segment end from the segment start to the polygon end
            {
 
                if ((i != 0) || (j != polygon.size() - 1))
                // skip checks if the diagonal is the last side
                {
                    // check if diagonal, cutting the segment off, is...
 
                    // ...intersecting any sides, except for ones having common verticies with it
                    bool flag = false;
 
                    dp[i][j] = 0;
 
                    // go through sides
                    for (size_t k = 0; k < polygon.size(); k++)
                    {
                        // checking the "k to (k + 1)" side
 
                        // carefull with going out of the vector
                        size_t s_k = (k + 1) % polygon.size();
 
                        if ((k == i) || (k == j) || (s_k == i) || (s_k == j))
                        // exclude the ones with common verticies
                        {
                            continue;
                        }
 
                        if (is_intersecting(polygon[i], polygon[j], polygon[k], polygon[s_k]))
                        // check if intersect
                        {
                            flag = true;
                            break;
                        }
                    }
 
                    if (flag)
                    {
                        continue;
                    }
 
                    if (relative_pos(middle(polygon[i], polygon[j]), polygon) != 1)
                    // ...doesn't have a point inside the polygon
                    {
                        continue;
                    }
                }
 
                // if passed, then the diagonal is viable - calculate the dp by checking all the triangles the diagonal can be in
                for (size_t k = i + 1; k < j; k++)
                {
                    dp[i][j] += (dp[i][k] * dp[k][j]) % MOD;
                    dp[i][j] %= MOD;
                }
            }
        }
 
        // scale back
        for (point<T> &v : polygon)
        {
            v.x /= 2;
            v.y /= 2;
        }
 
        return dp[0][polygon.size() - 1] % MOD;
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
 
    std::cout << geometry::triangulation_count(polygon) << '\n';
}
