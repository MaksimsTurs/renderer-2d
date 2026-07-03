#ifndef H_RENDERER2D_MATRIX
#define H_RENDERER2D_MATRIX

#include "type.h"
#include "vector.h"

typedef struct {
  vec2f32_t x, y;
} mat2x2f32_t;

typedef struct {
  vec3f32_t x, y, z;
} mat3x3f32_t;

void mat3x3f32_apply(mat3x3f32_t* matrix, vec2i32_t origin, vec2i32_t* vertecies, vec2i32_t* buffer, i8_t length);
mat3x3f32_t mat3x3f32_orthographic(f32_t length, f32_t right, f32_t top, f32_t bottom);
mat3x3f32_t mat3x3f32_multiply(mat3x3f32_t* a, mat3x3f32_t* b);
mat3x3f32_t mat3x3f32_inverse(mat3x3f32_t* matrix);

#endif
