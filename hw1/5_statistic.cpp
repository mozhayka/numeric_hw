class Statistics {
public:
  void update(float x);            // добавить новый элемент
  int count() const noexcept;
  float min() const noexcept;
  float max() const noexcept;
  float sum() const noexcept;
  float mean() const noexcept;     // среднее
  float variance() const noexcept; // дисперсия
};