float lerp_v1(float a, float b, float t) {
  return a + t*(b - a);
}

float lerp_v2(float a, float b, float t) {
  return (1.f-t)*a + t*b;
}