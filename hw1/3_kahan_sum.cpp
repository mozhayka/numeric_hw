#include <iostream>
#pragma GCC push_options
#pragma GCC optimize ("O0")

float kahan_sum(const float* x, int n) 
{
    float s = 0;
    float c = 0;
    for (int i = 0; i < n; i++) 
    {
        float y = x[i] - c;
        float t = s + y;
        c = (t - s) - y;
        s = t;
    }
    return s;
}

#pragma GCC pop_options

void test() 
{
    const int deg = 10000;
    const int n = 13 * deg;
    const float elem = 1.0 / 13.0;
    const float real_sum = 1.0 * deg;
    float simple_sum = 0.0;

    float x[n];
    for (int i = 0; i < n; i++)
    {
        x[i] = elem;
        simple_sum += x[i];
    }
    std::cout << "real sum: " << real_sum << '\n';
    std::cout << "simple sum: " << simple_sum << '\n';
    std::cout << "kahan sum: " << kahan_sum(x, n) << '\n';
}

int main()
{
    test();
}
