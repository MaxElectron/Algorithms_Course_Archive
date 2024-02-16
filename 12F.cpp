/*Дано N
 точек на плоскости. Нужно построить их выпуклую оболочку. Гарантируется, что выпуклая оболочка является невырожденной.

Входные данные
В первой строке число N
 (3≤N≤105
). Следующие N
 строк содержат пары целых чисел x
 и y
 (−109≤x,y≤109
) – координаты точек.

Выходные данные
В первой строке выведите N
 – число вершин выпуклой оболочки. Следующие N
 строк должны содержать координаты вершин в порядке обхода. Никакие три подряд идущие точки не должны лежать на одной прямой.*/

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
    std::vector<point<T>> upper_convex_hull(std::vector<point<T>> &set)
    {
        std::vector<point<T>> ans;

        for (point<T> next : set)
        {
            if (ans.size() < 2)
            {
                ans.push_back(next);
                continue;
            }
            vector<T> lhs (ans[ans.size() - 2], ans[ans.size() - 1]);
            vector<T> rhs (ans[ans.size() - 1], next);
            while ((lhs & rhs) >= 0)
            {
                ans.pop_back();
                if (ans.size() < 2)
                {
                    break;
                }
                lhs = vector<T> (ans[ans.size() - 2], ans[ans.size() - 1]);
                rhs = vector<T> (ans[ans.size() - 1], next);
            }
            ans.push_back(next);
        }

        return ans;
    }

    template <typename T>
    std::vector<point<T>> lower_convex_hull(std::vector<point<T>> &set)
    {
        std::vector<point<T>> ans;

        for (point<T> next : set)
        {
            if (ans.size() < 2)
            {
                ans.push_back(next);
                continue;
            }
            vector<T> lhs (ans[ans.size() - 2], ans[ans.size() - 1]);
            vector<T> rhs (ans[ans.size() - 1], next);
            while ((lhs & rhs) <= 0)
            {
                ans.pop_back();
                if (ans.size() < 2)
                {
                    break;
                }
                lhs = vector<T> (ans[ans.size() - 2], ans[ans.size() - 1]);
                rhs = vector<T> (ans[ans.size() - 1], next);
            }
            ans.push_back(next);
        }

        return ans;
    }

    template <typename T>
    std::vector<point<T>> convex_hull(std::vector<point<T>> &set)
    // accepts sorted vectors only
    {

        std::vector<point<T>> hull;

        std::vector<point<T>> top = upper_convex_hull(set);

        std::vector<point<T>> bottom = lower_convex_hull(set);

        std::reverse(bottom.begin(), bottom.end());

        top.pop_back();
        bottom.pop_back();
        for (point<T> p : top)
        {
            hull.push_back(p);
        }

        for (point<T> p : bottom)
        {
            hull.push_back(p);
        }

        return hull;
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

    std::vector<geometry::point<long long>> set(n);

    for (geometry::point<long long> &point : set)
    {
        std::cin >> point.x >> point.y;
    }

    std::sort(set.begin(), set.end(), [](geometry::point<long long> a, geometry::point<long long> b) {
        return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y));
    });

    std::vector<geometry::point<long long>> hull = geometry::convex_hull(set);

    std::cout << '\n' << hull.size() << '\n';

    for (geometry::point<long long> &point : hull)
    {
        std::cout << point.x << ' ' << point.y << '\n';
    }
}
