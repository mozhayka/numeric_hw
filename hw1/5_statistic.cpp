#include <algorithm>

class Statistics {
  int n = 0;
  float _min = 0;
  float _max = 0;
  float _sum = 0;
  float _mean = 0;
  float M = 0;
public:
  void update(float x);            // добавить новый элемент
  int count() const noexcept;
  float min() const noexcept;
  float max() const noexcept;
  float sum() const noexcept;
  float mean() const noexcept;     // среднее
  float variance() const noexcept; // дисперсия
};

void Statistics::update(float x) 
{
    if (n == 0) {
        _min = x;
        _max = x;
    } else {
        _min = std::min(x, _min);
        _max = std::max(x, _max);
    }
    _sum += x;
    n++;

    float new_mean = _mean + (x - _mean) / (float) n;
    M += (x - _mean) * (x - new_mean);
    _mean = new_mean;
}

int Statistics::count() const noexcept 
{
    return n;
}

float Statistics::min() const noexcept 
{
    return _min;
}

float Statistics::max() const noexcept 
{
    return _max;
}

float Statistics::sum() const noexcept 
{
    return _sum;
}

float Statistics::mean() const noexcept 
{
    return _mean;
}

float Statistics::variance() const noexcept 
{
    return M / (float) n;
}