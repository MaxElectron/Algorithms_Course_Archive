/*Даны два ненулевых вектора. Требуется вычислить:

Длину первого и второго вектора (два числа)
Вектор, образованный сложением данных двух векторов
Скалярное и векторное произведения данных векторов
Площадь треугольника, построенного из этих векторов
Входные данные
В двух строках входного файла заданы по четыре целых числа, не превосходящих по модулю 10000
, — координаты начала и конца первого вектора, затем второго.

Выходные данные
В каждой строке выходного файла — ответ на соответствующий пункт задачи с точностью не менее 10−6
.*/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <type_traits>

namespace geometry
{

    // No const handling because not needed, needs to be added if used in projects

    template <typename T>
    struct point
    {
        T x, y;
        point(T x_value, T y_value) : x(x_value), y(y_value) {}
    };

    template <typename T>
    class vector
    {
    public:
        vector(point<T> start_pos, point<T> end_pos) : value(point<T>(end_pos.x - start_pos.x, end_pos.y - start_pos.y)) {}

        vector(point<T> radius_end_pos) : value(radius_end_pos) {}

        T lenght()
        {
            if (std::is_integral<T>::value)
            {
                return T(std::round(std::sqrt(double(value.x * value.x + value.y * value.y))));
            }
            return T(std::sqrt(value.x * value.x + value.y * value.y));
        }

        T get_x() 
        {
            return value.x;
        }

        T get_y() 
        {
            return value.y;
        }

        vector &operator-()
        {
            value.x *= -1;
            value.y *= -1;
            return *this;
        }

        vector &operator+=(vector rhs)
        {
            value.x += rhs.value.x;
            value.y += rhs.value.y;
            return *this;
        }

        friend vector operator+(vector lhs, vector &rhs)
        {
            lhs += rhs;
            return lhs;
        }

        // product value
        friend T operator*(vector &lhs, vector &rhs)
        {
            return lhs.value.x * rhs.value.x + lhs.value.y * rhs.value.y;
        }

        // vector product value
        friend T operator&(vector &lhs, vector &rhs)
        {
            return lhs.value.x * rhs.value.y - lhs.value.y * rhs.value.x;
        }

    private:
        point<T> value;
    };
}

int main()
{

    long double x1, y1, x2, y2;

    std::cin >> x1 >> y1 >> x2 >> y2;
    geometry::vector<long double> a (geometry::point<long double>(x1, y1), geometry::point<long double>(x2, y2));

    std::cin >> x1 >> y1 >> x2 >> y2;
    geometry::vector<long double> b (geometry::point<long double>(x1, y1), geometry::point<long double>(x2, y2));

    std::cout << std::setprecision(10) << a.lenght() << ' ' << b.lenght() << '\n' << std::round((a + b).get_x()) << ' ' << std::round((a + b).get_y()) << '\n' << a * b << ' ' << (a & b) << '\n' << std::abs(a & b) / 2;

}
