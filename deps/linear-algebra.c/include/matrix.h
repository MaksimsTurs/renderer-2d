#ifndef H_LINEARALGEBRA_MATRIX
#define H_LINEARALGEBRA_MATRIX

#include <math.h>

#include "type.h"

typedef struct {
  f32_t data[9];
} mat3x3f32_t;

mat3x3f32_t mat3x3f32_mul_mat3x3f32(const mat3x3f32_t* a, const mat3x3f32_t* b);
void        mat3x3f32_mul_vec2f32(const mat3x3f32_t* a, f32_t* x, f32_t* y);
mat3x3f32_t mat3x3f32_inverse(const mat3x3f32_t *matrix);
f32_t       mat3x3f32_determinant(const mat3x3f32_t* matrix);
mat3x3f32_t mat3x3f32_projection_orthographic(f32_t left, f32_t right, f32_t top, f32_t bottom);
mat3x3f32_t mat3x3f32_view(f32_t x, f32_t y, f32_t rotation);
mat3x3f32_t mat3x3f32_translation(f32_t x, f32_t y);
mat3x3f32_t mat3x3f32_rotation(f32_t angle);
mat3x3f32_t mat3x3f32_scale(f32_t x, f32_t y);

#endif
