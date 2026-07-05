#ifndef H_RENDERER2D_MATRIX
#define H_RENDERER2D_MATRIX

#include <math.h>

#include "type.h"
#include "vector.h"
#include "utils.h"

typedef struct {
  vec3f32_t x, y, z;
} mat3x3f32_t;

void mat3x3f32_apply_to_shape(mat3x3f32_t* matrix, vec2f32_t origin, vec2f32_t* vertecies, vec2f32_t* buffer, i8_t length);

vec2f32_t   mat3x3f32_multiply_vec2f32(mat3x3f32_t* matrix, vec2f32_t vector);
mat3x3f32_t mat3x3f32_multiply_mat3x3f32(mat3x3f32_t* a, mat3x3f32_t* b);

mat3x3f32_t mat3x3f32_orthographic(f32_t left, f32_t right, f32_t top, f32_t bottom);
mat3x3f32_t mat3x3f32_view(vec2f32_t translation, f32_t rotation);
mat3x3f32_t mat3x3f32_inverse(mat3x3f32_t* matrix);
mat3x3f32_t mat3x3f32_translation(vec2f32_t translation);
mat3x3f32_t mat3x3f32_rotation(f32_t angle);

#endif
