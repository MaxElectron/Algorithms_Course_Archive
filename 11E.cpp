/*Даны два многочлена

A(x)=anxn+an−1xn−1+⋯+a0
B(x)=bmxm+bm−1xm−1+⋯+b0
Вычислите C(x)=A(x)⋅B(x)
Входные данные
n,an,an−1,…,a0
m,bm,bm−1,…,b0
0≤n,m<216
, |ai|,|bj|≤9
an≠0,bm≠0
Выходные данные
Выведите коэффициенты C
 в том же формате*/

#include <algorithm>
#include <complex>
#include <cmath>
#include <iostream>
#include <vector>

// code from https://www.geeksforgeeks.org/smallest-power-of-2-greater-than-or-equal-to-n/
int next_power_of_two(int n)
{
    int p = 1;
    if (n && !(n & (n - 1)))
        return n;

    while (p < n)
        p <<= 1;

    return p;
}

// code based on https://www.youtube.com/watch?v=h7apO7q16V0&ab_channel=Reducible
// and https://www.geeksforgeeks.org/fast-fourier-transformation-poynomial-multiplication/
std::vector<std::complex<double>> FFT(std::vector<std::complex<double>> &coefficients)
{
    // Base case
    if (coefficients.size() == 1)
    {
        return coefficients;
    }

    // Magic numbers here
    std::vector<std::complex<double>> omega(coefficients.size());
    for (size_t i = 0; i < coefficients.size(); i++)
    {
        double alpha = -2 * 3.14159265358979323846 * i / coefficients.size();
        omega[i] = std::complex<double>(std::cos(alpha), std::sin(alpha));
    }

    // Split into to interlacing parts
    std::vector<std::complex<double>> even(coefficients.size() / 2);
    std::vector<std::complex<double>> odd(coefficients.size() / 2);
    for (size_t i = 0; i < (coefficients.size()) / 2; i++)
    {
        even[i] = coefficients[i * 2];
        odd[i] = coefficients[i * 2 + 1];
    }

    // Perform recursively
    even = FFT(even);
    odd = FFT(odd);
    std::vector<std::complex<double>> ans(coefficients.size(), 0);

    // Merge from recursion
    for (size_t i = 0; i < coefficients.size() / 2; i++)
    {
        ans[i] = std::complex<double>(even[i]) + omega[i] * std::complex<double>(odd[i]);
        ans[i + coefficients.size() / 2] = std::complex<double>(even[i]) - omega[i] * std::complex<double>(odd[i]);
    }

    // Return the answer
    return ans;
}

std::vector<std::complex<double>> IFFT(std::vector<std::complex<double>> &coefficients)
{
    // Base case
    if (coefficients.size() == 1)
    {
        return coefficients;
    }

    // Magic numbers here
    std::vector<std::complex<double>> omega(coefficients.size());
    for (size_t i = 0; i < coefficients.size(); i++)
    {
        double alpha = -2 * 3.14159265358979323846 * i / coefficients.size();
        // Difference from FFT is here
        omega[i] = std::complex<double>(1.0) / std::complex<double>(std::cos(alpha), std::sin(alpha));
    }

    // Split into to interlacing parts
    std::vector<std::complex<double>> even(coefficients.size() / 2);
    std::vector<std::complex<double>> odd(coefficients.size() / 2);
    for (size_t i = 0; i < (coefficients.size()) / 2; i++)
    {
        even[i] = coefficients[i * 2];
        odd[i] = coefficients[i * 2 + 1];
    }

    // Perform recursively
    // Difference from FFT is here
    even = IFFT(even);
    odd = IFFT(odd);
    std::vector<std::complex<double>> ans(coefficients.size(), 0);

    // Merge from recursion
    for (size_t i = 0; i < coefficients.size() / 2; i++)
    {
        ans[i] = std::complex<double>(even[i]) + omega[i] * std::complex<double>(odd[i]);
        ans[i + coefficients.size() / 2] = std::complex<double>(even[i]) - omega[i] * std::complex<double>(odd[i]);
    }

    // Return the answer
    return ans;
}

std::vector<int> polynomial_multiplication(std::vector<int> &a_coefficients, std::vector<int> &b_coefficients)
{

    int new_size = 2 * std::max(next_power_of_two(a_coefficients.size()), next_power_of_two(b_coefficients.size()));
    a_coefficients.resize(new_size, 0);
    b_coefficients.resize(new_size, 0);

    std::vector<std::complex<double>> a_coefficients_complex (new_size);
    std::vector<std::complex<double>> b_coefficients_complex (new_size);

    // Transform into complex
    for (size_t i = 0; i < new_size; i++)
    {
        a_coefficients_complex[i] = std::complex<double> (a_coefficients[i]);
        b_coefficients_complex[i] = std::complex<double> (b_coefficients[i]);
    }
    

    std::vector<std::complex<double>> a_values = FFT(a_coefficients_complex);
    std::vector<std::complex<double>> b_values = FFT(b_coefficients_complex);
    std::vector<std::complex<double>> c_values(new_size, 0);

    for (size_t i = 0; i < new_size; i++)
    {
        c_values[i] = a_values[i] * b_values[i];
    }

    std::vector<std::complex<double>> c_coefficients_complex = IFFT(c_values);

    // Transform from complex

    std::vector<int> c_coefficients (new_size);

    for (size_t i = 0; i < new_size; i++)
    {
        // Some black magic from https://stackoverflow.com/questions/9695329/c-how-to-round-a-double-to-an-int
        c_coefficients[i] = ((std::real(c_coefficients_complex[i]) / new_size) + 0.5 - ((std::real(c_coefficients_complex[i]) / new_size) < 0));
    }

    // code from https://stackoverflow.com/questions/36526603/how-to-remove-trailing-0s-from-c-vector
    int i;
    for (i = c_coefficients.size() - 1; i >= 0 && c_coefficients[i] == 0; --i)
        ;
    c_coefficients.resize(i + 1);

    return c_coefficients;
}

int main()
{

    int n;
    std::cin >> n;
    std::vector<int> a_coefficients(n + 1);
    for (int &i : a_coefficients)
    {
        std::cin >> i;
    }
    std::reverse(a_coefficients.begin(), a_coefficients.end());

    int m;
    std::cin >> m;
    std::vector<int> b_coefficients(m + 1);
    for (int &i : b_coefficients)
    {
        std::cin >> i;
    }
    std::reverse(b_coefficients.begin(), b_coefficients.end());

    std::vector<int> c_coefficients = polynomial_multiplication(a_coefficients, b_coefficients);

    std::reverse(c_coefficients.begin(), c_coefficients.end());

    std::cout << c_coefficients.size() - 1 << ' ';

    for (int i : c_coefficients)
    {
        std::cout << i << ' ';
    }

    std::cout << std::endl;
}
