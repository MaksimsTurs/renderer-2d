#ifndef H_RENDERER2D_VECTOR
#define H_RENDERER2D_VECTOR

#include "type.h"

typedef struct {
  f32_t x, y;
} vec2f32_t;

typedef struct {
  f32_t x, y, z;
} vec3f32_t;

typedef struct {
  u32_t x, y;
} vec2u32_t;

typedef struct {
  i32_t x, y;
} vec2i32_t;

i32_t vec2i32_determinant(vec2i32_t a, vec2i32_t b, vec2i32_t c);

#endif
