#include <cmath>
#include <iostream>
#include <random>

using namespace std;

const int MAX_STEPS = 1e4;
const float pi = 3.1415926;
const float bisect_eps_x = 1e-4;
const float bisect_eps_f = 1e-5;
const float newton_eps_x = 1e-4;
const float newton_eps_f = 1e-5;
const float max_x_bisect = 10.0;
const float max_x_newton = 10.0;

float RastriginFunction(float x)
{
    return x * x + 10.0 + 10.0 * cos(2 * pi * x); 
}

float dRastriginFunction(float x)
{
    return 2.0 * x + 20.0 * pi * sin(2 * pi * x);
}

float ddRastriginFunction(float x)
{
    return 2.0 + 40.0 * pi * pi * cos(2 * pi * x);
}

struct AnswerWithStepsCount
{
    float ans;
    int steps;
};

bool isDiffSign(float a, float b)
{
    return a < 0 && b > 0 || a > 0 && b < 0;
}

AnswerWithStepsCount bisectRastriginFunction(float left, float right, int step = 0)
{
    float mid = (left + right) / 2;
    if (step > MAX_STEPS || fabs(left - right) < bisect_eps_x)
    {
        return {mid, step};
    }

    if (fabs(RastriginFunction(mid)) < bisect_eps_f)
    {
        return {mid, step};
    }

    float df_left = dRastriginFunction(left);
    float df_mid = dRastriginFunction(mid);
    float df_right = dRastriginFunction(right);

    if (isDiffSign(df_left, df_mid))
    {
        return bisectRastriginFunction(left, mid, step + 1);
    }
    else
    {
        return bisectRastriginFunction(mid, right, step + 1);
    }
}

AnswerWithStepsCount newtonRastriginFunction(float x, int step = 0)
{
    float df_x = dRastriginFunction(x);
    float ddf_x = ddRastriginFunction(x);

    if (step > MAX_STEPS || 
        fabs(df_x) < newton_eps_f || 
        fabs(ddf_x) < newton_eps_f)
    {
        return {x, step};
    }

    float new_x = x - df_x / ddf_x;

    if (fabs(new_x - x) < newton_eps_x)
    {
        return {x, step};
    }

    return newtonRastriginFunction(new_x, step + 1);
}

struct BisectPair
{
    float fst;
    float snd;
};

BisectPair genBisectPair(float max_x)
{
    float fst = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max_x));
    float snd = - static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max_x));
    return {fst, snd};
}

BisectPair genGoodBisectPair(float max_x = max_x_bisect)
{
    auto p = genBisectPair(max_x);
    float df_fst = dRastriginFunction(p.fst);
    float df_snd = dRastriginFunction(p.snd);
    if (isDiffSign(df_fst, df_snd))
    {
        return p;
    }
    return genGoodBisectPair(max_x);
}

void runBisectNTimes(int n)
{
    int sumSteps = 0;
    for (int i = 0; i < n; i++)
    {
        auto p = genGoodBisectPair();
        auto ans = bisectRastriginFunction(p.fst, p.snd);
        sumSteps += ans.steps;
    }

    cout << "Bisect Tries: " << n << endl;
    cout << "Bisect summary steps: " << sumSteps << endl;
    cout << "Bisect average steps: " << ((float) sumSteps) / n << endl;
}

float genNewtonX(float max_x)
{
    return max_x - static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2 * max_x));
}

void runNewtonNTimes(int n)
{
    int sumSteps = 0;
    for (int i = 0; i < n; i++)
    {
        auto x = genNewtonX(max_x_newton);
        auto ans = newtonRastriginFunction(x);
        sumSteps += ans.steps;
    }

    cout << "Newton Tries: " << n << endl;
    cout << "Newton summary steps: " << sumSteps << endl;
    cout << "Newton average steps: " << ((float) sumSteps) / n << endl;
}

int main()
{
    int n = 1000;
    srand (static_cast <unsigned> (time(0)));
    runBisectNTimes(n);
    runNewtonNTimes(n);
}