#include "../include/vector.h"
#include <stdio.h>

// gcc -Llibs tests/vector.c -o main -lm -l:libvector.a

int main(void)
{
  vec2f32_t a = {12.5f, 25.75f};
  vec2f32_t b = {55.65f, 605.75f};
  vec2f32_t ab = {0};
  vec2f64_t norm = {0.0f};
  f32_t f = 0.0f;

  ab = vec2f32_add(&a, &b);
  printf("%.2f %.2f\n", ab.x, ab.y);

  ab = vec2f32_sub(&a, &b);
  printf("%.2f %.2f\n", ab.x, ab.y);

  ab = vec2f32_scale(&a, 2.0f);
  printf("%.2f %.2f\n", ab.x, ab.y);

  norm = vec2f32_normalize(&a);
  printf("%.2f %.2f\n", norm.x, norm.y);

  f = vec2f32_dot(&a, &b);
  printf("%.2f\n", f);

  f = vec2f32_length(&a);
  printf("%.2f\n", f);
}
