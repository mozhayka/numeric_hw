#include <iostream>
#include <ctime>


#pragma GCC push_options

float pairwise_sum_simd(float* x, int n) 
{
    if (n == 1) 
    {
        return x[0];
    }

#pragma omp simd

    for (int i = 0; i < n / 2; i++) 
    {
        x[i] += x[i + (n + 1) / 2];
    }
    
    return pairwise_sum_simd(x, (n + 1) / 2);
}

#pragma GCC pop_options

float simple_acc_sum(float* x, int n)
{
    float ans = 0.0;
    for (int i = 0; i < n; i++)
    {
        ans += x[i];
    }
    return ans;
}

double calculate_duration(float* x, int n, bool is_simple, int repeats, double elem)
{
    double sum;
    double bad_time = 0.0;
    std::clock_t start;
    start = std::clock();    
    for (int j = 0; j < repeats; j++)
    {
        double start_bad_time = std::clock();    
        for (int i = 0; i < n; i++)
        {
            x[i] = elem;
        }
        bad_time += ( std::clock() - start_bad_time ) / (double) CLOCKS_PER_SEC;

        if (is_simple) 
        {
            simple_acc_sum(x, n);
        }
        else 
        {
            pairwise_sum_simd(x, n);
        }
    }
    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    return duration - bad_time;
}

void test() 
{
    const int deg = 10000;
    const int n = 13 * deg;
    const float elem = 1.0 / 13.0;
    const float real_sum = 1.0 * deg;
    const int repeats = 10000;

    float x[n];
    for (int i = 0; i < n; i++)
    {
        x[i] = elem;
    }
    double simple_sum = simple_acc_sum(x, n);
    double pairwise_sum = pairwise_sum_simd(x, n);

    std::cout << "real sum: " << real_sum << '\n';
    std::cout << "simple sum: " << simple_sum << " duration: " << calculate_duration(x, n, true, repeats, elem) << '\n';
    std::cout << "pairwise sum: " << pairwise_sum << " duration: " << calculate_duration(x, n, true, repeats, elem) << '\n';
}

int main()
{
    test();
}
