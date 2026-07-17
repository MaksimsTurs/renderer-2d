#include "../include/transform.h"
#include <stdio.h>

// gcc -Llibs tests/transform.c -o main -lm -l:libtransform.a

int main(void) 
{
  transform2d_t transform = {0};
  vec2f32_t position = {10.0f, 10.0f};
  vec2f32_t target = {20.0f, 20.0f};
  transfrom2d_look_at(&transform, &position, &target);

  printf("%.2f\n", transform.rotation);
}
