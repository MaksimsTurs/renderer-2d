#ifndef H_RENDERER2D_VECTOR
#define H_RENDERER2D_VECTOR

#include "type.h"

typedef struct {
  f32_t x, y;
} vec2f32_t;

typedef struct {
  u32_t x, y;
} vec2u32_t;

i32_t vec2u32_calc_determinant(vec2u32_t a, vec2u32_t b, vec2u32_t c);

#endif
