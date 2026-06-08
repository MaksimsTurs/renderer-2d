#ifndef H_RENDERER2D_MATH
#define H_RENDERER2D_MATH

#include <math.h>

#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b

typedef struct vec2f_s {
  float x, y;
} vec2f_t;

typedef struct vec3f_s {
  float x, y, z;
} vec3f_t;

typedef struct mat3x3f_s {
  vec3f_t x[3], y[3], z[3];
} mat3x3f_t;

mat3x3f_t mat3x3f_new(vec3f_t translation, vec3f_t scale, float rotation);
void mat3x3f_apply(mat3x3f_t* matrix, vec2f_t* verticies, unsigned char count);

#endif
