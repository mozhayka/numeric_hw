#include <cmath>

// a - массив коэффициентов
// n - длина массива коэффициентов a
float polynomial(float x, const float* a, int n) 
{
    float ans = a[n - 1];
    for (int i = n - 2; i >= 0; i--) 
    {
        ans = std::fma(ans, x, a[i]);
    }
    return ans;
}
