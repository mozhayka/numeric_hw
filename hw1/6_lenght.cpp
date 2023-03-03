#include <cmath>
#include <iostream>

float length(const float* x, int n)
{
    float m = 1.0;
    float _sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        float abs_i = std::fabs(x[i]);
        if (abs_i > m)
        {
            _sum *= (m / abs_i) * (m / abs_i);
            m = abs_i;
        }
        _sum += (abs_i / m) * (abs_i / m);
    }
    return m * std::sqrt(_sum);
}

void test()
{
    float x[5] = {3.0, 4.0, 5.0, 5.0, 5.0};
    std::cout << length(x, 5) << '\n';
}

int main()
{
    test();
}