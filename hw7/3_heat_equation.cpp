#include <cmath>
#include <iostream>
#include <random>

using namespace std;

const float pi = M_PI;
const float inf = 1e9;
const int max_steps = 1e3;

float f(float x_, float x, float t, float alpha)
{
    return exp(-x_ * x_) * exp(-(x - x_) * (x - x_) / 2 * alpha * t);
}

float integrate(float from, float to, float x, float t, float alpha, int n)
{
    float sum = 0;
    float step = (from - to) / n;
    for (int i = 1; i < n; i++)
    {
        float x_i_minus_1 = from + step * (i - 1);
        float x_i = x_i_minus_1 + step;

        float f_x_i_minus_1 = f(x_i_minus_1, x, t, alpha);
        float f_x_i = f(x_i, x, t, alpha);

        sum += step * (f_x_i + f_x_i_minus_1) / 2;
    }
    return sum / (2 * sqrt(pi * alpha * t));
}

struct result
{
    float temperature;
    float end_time;
};


result calculate_temperature_until_equality(float len, float time_step, float alpha, float eps, int n, int m)
{
    float cur_time = 0;
    float distance = len / m;
    for (int _ = 0; _ < max_steps; _++)
    {
        cur_time += time_step;
        float max_temperature = -inf;
        float min_temperature = inf;

        for (int i = 0; i < m; i++)
        {
            float temperature = integrate(0, len, distance * i, cur_time, alpha, n);
            min_temperature = min(min_temperature, temperature);
            max_temperature = max(max_temperature, temperature);
        }

        if (max_temperature - min_temperature < eps)
        {
            return {min_temperature, cur_time};
        }
    }
    return {-1, -1};
}

int main()
{
    float len = 10;
    float time_step = 1;
    float alpha = 30;
    float eps = 1e-2;
    int n = 5;
    int m = 3;
    auto ans = calculate_temperature_until_equality(len, time_step, alpha, eps, n, m);
    cout << "Final temperature " << ans.temperature << endl;
    cout << "Time spent " << ans.end_time << endl;
}