#ifndef H_LINEARALGEBRA_TRANSFORM
#define H_LINEARALGEBRA_TRANSFORM

#include <math.h>

#include "type.h"
#include "vector.h"

typedef struct {
  vec2f32_t translation;
  vec2f32_t origin;
  vec2f32_t scale;
  f32_t rotation;
} transform2d_t;

void transfrom2d_look_at(transform2d_t* transform, const vec2f32_t* position, const vec2f32_t* target);
void transform2d_to_mat3x3f32(const transform2d_t* transform, f32_t buffer[9]);

#endif
